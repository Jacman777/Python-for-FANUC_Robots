# Example Python code to use FANUC Robot Python executor for socket communication
# Version: 0.1
# Prepared by Jacek Urbanowicz 
import socket
import time
import os
from pymodbus.exceptions import ConnectionException, NotImplementedException
import fanucrobot.robotif as rbif

def create_socket():
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    return s

def connect_to_server(s, host, port):
    try:
        s.connect((host, port))
        print("Connected to server")
        return True
    except socket.error as e:
        print(f"Connection error: {e}")
        return False

def connect_to_Robot(host, port, retries=3, delay=5):
    for attempt in range(retries):
        try:
            print(f"Attempt {attempt + 1} of {retries}")
            Robot.connect(host, port)
            print("Connected to robot")
            return
        except:
            print(f"RO connect attempt {attempt + 1} failed, IP:{host}, port:{port}")
            time.sleep(delay)
    print("All retry attempts failed. Please check the Ethernet connection and MODBUS connection settings.")

def main():
    deviceID = "2"
    print(f"OS name: {os.name}")
    host = '192.168.0.177'      # Socket server IP address
    port = 9900                 # Socket server port
    RO_host = '127.0.0.1'       # Robot Modbus IP address
    RO_port = 502               # Robot Modbus port
    reconnect_delay = 5         # Delay before reconnecting in seconds for socket communication
    s = create_socket()
  
    global Robot 
    Robot = rbif.Core()         # Create Core Robot object
    dataTable1 = Robot.get_datatable()
    #Create Datatable for Robot communication
    #Add Robot Numeric Registers to monitor
    floatreg5 = dataTable1.add_numreg(valuetype=float,start_idx=5,end_idx=5)
    #Add Robot variables (DATA ID's) to monitor
    ROvars1 = dataTable1.add_variable(vartype=float,varname="$DIAGNOSIS.OVERCURRENT_RATIO[1,2]")                # J2 axis overcurrent
    ROvars2 = dataTable1.add_variable(vartype=float,varname="$SERVO_FEEDBACK.POSITION_JOINT[1,2]",program=None) # J2 axis position
    ROvars3 = dataTable1.add_variable(vartype=int,varname="$MOTION_CONTROL.OVERRIDE",program=None)              # Override percentage
    ROvars4 = dataTable1.add_variable(vartype=int,varname="$PROGRAM_EXECUTION.IN_SINGLE_STEP_MODE",program=None)# STEP status

    
    # Connect to Robot controller
    connect_to_Robot(RO_host,RO_port)
    # Reconnect in case connection is not established
    while not connect_to_server(s, host, port):
        print(f"Reconnecting in {reconnect_delay} seconds...")
        time.sleep(reconnect_delay)
        s = create_socket()  # Create a new socket for each reconnection attempt
    # Set FLAG[5] to on when connected
    Robot.write_FLAG(index=5, values=[True])
    try:
        headerMsg = "Timestamp,Device_ID,Data_Type,Value\n"
        s.sendall(headerMsg.encode('utf-8'))
        endOfRecording = [False]
        # Main data logging loop
        while not endOfRecording[0]:
            dataTable1.refresh() 
            # Convert the timestamp to a struct_time
            current_time = time.gmtime()
            current_time_with_ms = time.time()
            # Extract milliseconds
            milliseconds = int((current_time_with_ms - int(current_time_with_ms)) * 1000)
            # Format the time as a string
            formatted_time = time.strftime('%Y-%m-%d %H:%M:%S', current_time)
            formatted_time_with_ms = f'{formatted_time}.{milliseconds:03d}'
            print('Current system time (UTC) with milliseconds:', formatted_time_with_ms)
            # Read DI[]
            do_10 = Robot.read_DO(10,1)
            message = formatted_time_with_ms +","+deviceID+",DI[10],"+str(do_10[0])+"\n"
            s.sendall(message.encode('utf-8'))
            # Read R[]
            r_5 = floatreg5.getvalue(index=5)
            message = formatted_time_with_ms +","+deviceID+",R[5],"+str(r_5)+"\n"
            s.sendall(message.encode('utf-8'))
            # Read DATA ID: J2 Overcurrent
            ovc_J2 = ROvars1.getvalue()
            message = formatted_time_with_ms +","+deviceID+",OVC_J2,"+str(round(ovc_J2,3))+"\n"
            s.sendall(message.encode('utf-8'))
            print('ovc j2: ',ovc_J2)
            # Read DATA ID: J2 Position
            pos_J2 = ROvars2.getvalue()
            message = formatted_time_with_ms +","+deviceID+",Position_J2,"+str(round(pos_J2,2))+"\n"
            s.sendall(message.encode('utf-8'))
            print('Pos j2: ',pos_J2)            
            # Read DATA ID: General Override
            override = ROvars3.getvalue()
            message = formatted_time_with_ms +","+deviceID+",Override,"+str(override)+"\n"
            s.sendall(message.encode('utf-8'))
            print('override: ', override)
            # Read DATA ID: SINGLE STEP status
            step = ROvars4.getvalue()
            message = formatted_time_with_ms +","+deviceID+",STEP_ENB,"+str(step)+"\n"
            print('step: ',step)
            s.sendall(message.encode('utf-8'))
            # Check FLAG[6] - end of data recording
            endOfRecording = Robot.read_FLAG(index=6,count=1)
            message = formatted_time_with_ms +","+deviceID+",F[6],"+str(endOfRecording)+"\n"
            s.sendall(message.encode('utf-8'))
            time.sleep(1)

    except KeyboardInterrupt:
        print("Client closed")
    finally:
        s.close()
        Robot.disconnect()
        del Robot

if __name__ == "__main__":
    
    main()