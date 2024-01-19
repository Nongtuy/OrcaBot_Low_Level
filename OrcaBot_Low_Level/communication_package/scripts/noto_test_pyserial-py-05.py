#######################################################
#  Title: pySerialTransfer Test                       #
#  Version: 5                                         #
#  Author: Noto (Warit Yuvaniyama)                    #
#  Last edited: 2024/01/05                            #
#  Description: Stand alone test for pySerialTransfer #
#######################################################

## Problem: when adding kick_2 to the orca_dict, the data is too Large for the buffer (max 254) [Solved in V.4]
##          Old use 246 bytes (8 bytes left), New use 270 bytes (Over by 16 bytes)
## Solution: split the orca_dict into 2 parts, send the first part, then send the second part

## Implementing Holo_input data by generating random value for each robot

## Implementing Holodrive algorithm to calculate the power for each motor

## Note: To receive the data back from Arduino the process must be
##       1. Send the data [max 254 bytes] (orca_dict_1)
##       2. Wait for a response with while not link.available():
##       3. Parse feedback from Arduino
## Note 2: The velocity, angular velocity, and gear ratio is updated to a new value 
##         please make sure that every team is informed about this change
##         max velocity = 521.0333 mm/s, max angular velocity = 5.78926 rad/s
##         gear ratio = 11/30


import time
from math import sin, cos, radians
from pySerialTransfer import pySerialTransfer as txfer
from icecream import ic
import random as r
# Don't forget to import the library >> pip install icecream (for debuging) and other library

Serial_port = 'COM4'
send_size = 0

# Input dictionary
# format = {robot_id : [V_x (float), V_y (float), V_ang (float), kick_1 (bool), kick_2 (bool), dribbler (bool)]
# Generate a random value for each robot (for testing)
# max velocity = 521.0333 mm/s, max angular velocity = 5.78926 rad/s
# Holo_input = {'0': [r.uniform(-521.03,521.03), r.uniform(-521.03,521.03), r.uniform(-5.78926,5.78926), r.randint(0,1), r.randint(0,1), 1],
#               '1': [r.uniform(-521.03,521.03), r.uniform(-521.03,521.03), r.uniform(-5.78926,5.78926), r.randint(0,1), r.randint(0,1), 1],
#               '2': [r.uniform(-521.03,521.03), r.uniform(-521.03,521.03), r.uniform(-5.78926,5.78926), r.randint(0,1), r.randint(0,1), 1],
#               '3': [r.uniform(-521.03,521.03), r.uniform(-521.03,521.03), r.uniform(-5.78926,5.78926), r.randint(0,1), r.randint(0,1), 1],
#               '4': [r.uniform(-521.03,521.03), r.uniform(-521.03,521.03), r.uniform(-5.78926,5.78926), r.randint(0,1), r.randint(0,1), 1],
#               '5': [r.uniform(-521.03,521.03), r.uniform(-521.03,521.03), r.uniform(-5.78926,5.78926), r.randint(0,1), r.randint(0,1), 1]}
# ic(Holo_input)

# Network dictionary
# format = {robot_id : [Motor_0, Motor_1, Motor_2, Motor_3, Kicker_1, Kicker_2, Dribbler]
#          {    0    : [ 1024  , -1024  ,  1024  ,  -1024 ,    0    ,    0    ,   1    ]}
orca_dict = {'0': [0, 0, 0, 0, 0, 0, 1],
             '1': [0, 0, 0, 0, 0, 0, 1],
             '2': [0, 0, 0, 0, 0, 0, 1],
             '3': [0, 0, 0, 0, 0, 0, 1],
             '4': [0, 0, 0, 0, 0, 0, 1],
             '5': [0, 0, 0, 0, 0, 0, 1]}

def map_motor_value(value):
    min_value = -(15631/30) # -521.0333333333333
    max_value = 15631/30 # 521.0333333333333
    new_min = -1024
    new_max = 1024
    # Map the value to the new scale
    mapped_value = int((value - min_value) * (new_max - new_min) / (max_value - min_value) + new_min)
    return mapped_value

def HoloDrive_dict_extract(**kwargs):
    for key, value in kwargs.items():
        # ic(key, value)
        # use these 3 value to calculate the power for each motor
        V_x = value[0]
        V_y = value[1]
        V_ang = value[2]
        ic(V_x, V_y, V_ang)
        # Calculate the power for each motor with holo drive
        ### This parts is just a random equation for now, need to be change later ###        
        Motor_0 = (-1*(sin(radians(26.56))*V_x) + (cos(radians(26.56))*V_y) + V_ang)
        ic(Motor_0)
        Motor_0 = map_motor_value(Motor_0)
        Motor_1 = ((-1*sin(radians(153.44))*V_x) + (cos(radians(153.44))*V_y) + V_ang)
        ic(Motor_1)
        Motor_1 = map_motor_value(Motor_1)
        Motor_2 = ((-1*sin(radians(206.56))*V_x) + cos(radians(206.56))*V_y + V_ang)
        ic(Motor_2)
        Motor_2 = map_motor_value(Motor_2)
        Motor_3 = ((-1*sin(radians(333.44))*V_x) + cos(radians(333.44))*V_y + V_ang)
        ic(Motor_3)
        Motor_3 = map_motor_value(Motor_3)
        
        
        orca_dict[key] = [Motor_0, Motor_1, Motor_2, Motor_3, value[3], value[4], value[5]]
    return orca_dict
    
if __name__ == '__main__':
    link = txfer.SerialTransfer(Serial_port)
    
    try:
        ### Open the serial port ###
        # Just have to run link.open() and time.sleep(2) once
        link.open()
        time.sleep(2)  # wait for Arduino to reset
        while True:
            Holo_input = {'0': [r.uniform(-521.03,521.03), r.uniform(-521.03,521.03), r.uniform(-5.78926,5.78926), r.randint(0,1), r.randint(0,1), 1],
                          '1': [r.uniform(-521.03,521.03), r.uniform(-521.03,521.03), r.uniform(-5.78926,5.78926), r.randint(0,1), r.randint(0,1), 1],
                          '2': [r.uniform(-521.03,521.03), r.uniform(-521.03,521.03), r.uniform(-5.78926,5.78926), r.randint(0,1), r.randint(0,1), 1],
                          '3': [r.uniform(-521.03,521.03), r.uniform(-521.03,521.03), r.uniform(-5.78926,5.78926), r.randint(0,1), r.randint(0,1), 1],
                          '4': [r.uniform(-521.03,521.03), r.uniform(-521.03,521.03), r.uniform(-5.78926,5.78926), r.randint(0,1), r.randint(0,1), 1],
                          '5': [r.uniform(-521.03,521.03), r.uniform(-521.03,521.03), r.uniform(-5.78926,5.78926), r.randint(0,1), r.randint(0,1), 1]}
            # Holo_input = {'0': [521.03, 521.03, 5.78926, r.randint(0,1), r.randint(0,1), 1],
            #               '1': [-521.03, -521.03, 5.78926, r.randint(0,1), r.randint(0,1), 1],
            #               '2': [-521.03, 521.03, 5.78926, r.randint(0,1), r.randint(0,1), 1],
            #               '3': [521.03, 521.03, -5.78926, r.randint(0,1), r.randint(0,1), 1],
            #               '4': [-521.03, -521.03, -5.78926, r.randint(0,1), r.randint(0,1), 1],
            #               '5': [521.03, -521.03, -5.78926, r.randint(0,1), r.randint(0,1), 1]}
            ic(Holo_input)
            ### Formating data into orca_dict_1 and orca_dict_2 ###
            # format = {robot_id : [Motor_0, Motor_1, Motor_2, Motor_3, Kicker_1, Kicker_2, Dribbler]
            #          {    0    : [ 1024  , -1024  ,  1024  ,  -1024 ,    0    ,    0    ,   1    ]}
            dict(orca_dict, **HoloDrive_dict_extract(**Holo_input))
            ic(orca_dict)
            orca_dict_1 = {key: value for key, value in orca_dict.items() if int(key) in (0, 1, 2)}
            orca_dict_2 = {key: value for key, value in orca_dict.items() if int(key) in (3, 4, 5)}
            ic(orca_dict_1)
            ic(orca_dict_2)
            # -------------------------------------------------------------------------------------
            ### Send data ###
            start_commu_time = time.perf_counter()
            # >> tx_obj(val, start_pos=0, byte_format='', val_type_override='')
            ## First packet ##
            start_time = time.perf_counter()
            orca_tx = link.tx_obj(orca_dict_1, start_pos=send_size) - send_size # return the number of bytes in orca_dict_1
            send_size += orca_tx # update the number of bytes in the buffer
            link.send(send_size) # send the first data packat (orca_dict_1)
            send_size = 0 # reset the number of bytes in the buffer
            print(f"Sent: {orca_dict_1}")
            # Wait for a response and report any errors while receiving packets
            timeout = 0.060  # 60 ms timeout
            start_time = time.perf_counter()
            while not link.available():
                if link.status < 0:
                    if link.status == txfer.CRC_ERROR:
                        print('ERROR: CRC_ERROR')
                    elif link.status == txfer.PAYLOAD_ERROR:
                        print('ERROR: PAYLOAD_ERROR')
                    elif link.status == txfer.STOP_BYTE_ERROR:
                        print('ERROR: STOP_BYTE_ERROR')
                    else:
                        print('ERROR: {}'.format(link.status))
                if time.perf_counter() - start_time > timeout:
                    print(f'Timeout: No response received within {timeout} seconds')
                    break
            # Parse feedback from Arduino
            orca_rx_dict = link.rx_obj(obj_type=type(orca_dict),
                                       start_pos=0,
                                       obj_byte_size=orca_tx,
                                       list_format=b'i')  # Convert the format string to bytes
            print(f"Received: {orca_rx_dict}")
            # -------------------------------------------------------------------------------------
            ## Second packet ##            
            orca_tx = link.tx_obj(orca_dict_2, start_pos=send_size) - send_size # return the number of bytes in orca_dict_2
            send_size += orca_tx # update the number of bytes in the buffer
            link.send(send_size) # send the second data packat (orca_dict_2)
            send_size = 0 # reset the number of bytes in the buffer
            print(f"Sent: {orca_dict_2}")
            # Wait for a response and report any errors while receiving packets
            timeout = 0.06  # 60 ms timeout
            while not link.available():
                if link.status < 0:
                    if link.status == txfer.CRC_ERROR:
                        print('ERROR: CRC_ERROR')
                    elif link.status == txfer.PAYLOAD_ERROR:
                        print('ERROR: PAYLOAD_ERROR')
                    elif link.status == txfer.STOP_BYTE_ERROR:
                        print('ERROR: STOP_BYTE_ERROR')
                    else:
                        print('ERROR: {}'.format(link.status))
                if time.perf_counter() - start_time > timeout:
                    print(f'Timeout: No response received within {timeout} seconds')
                    break
            # Parse feedback from Arduino
            orca_rx_dict = link.rx_obj(obj_type=type(orca_dict),
                                       start_pos=0,
                                       obj_byte_size=orca_tx,
                                       list_format=b'i')  # Convert the format string to bytes
            print(f"Received: {orca_rx_dict}")
            # -------------------------------------------------------------------------------------
            ### Display the received data ###
            stop_commu_time = time.perf_counter()
            print(f"Time: {stop_commu_time - start_commu_time}")
            ic(orca_tx)
             
    except KeyboardInterrupt:
        try:
            link.close()
        except:
            pass
        print('KeyboardInterrupt')
    except:
        import traceback
        traceback.print_exc()

        try:
            link.close()
        except:
            pass
        print('Exiting.')