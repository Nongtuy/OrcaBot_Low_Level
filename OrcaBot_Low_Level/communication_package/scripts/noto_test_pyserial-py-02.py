import time
import numpy as np
from pySerialTransfer import pySerialTransfer as txfer
from icecream import ic

send_size = 0

# format = {robot_id : [Motor_0, Motor_1, Motor_2, Motor_3, Kicker, Dribbler]
#               0    : [ 1024  , -1024  ,  1024  ,  -1024 ,   0   ,   1    ]}

if __name__ == '__main__':
    # Initialize the serial transfer object
    link = txfer.SerialTransfer('COM4')
    try:
    ### Open the serial port ###
        link.open()
        time.sleep(2)  # wait for Arduino to reset
        
    ### Send data ###    
        sent_str = ''
        for i in range(3):
            test_str = "hello arduino " + str(i) + '\t'
            tx_msg_01 = link.tx_obj(test_str, start_pos=send_size) - send_size
            send_size += tx_msg_01
            sent_str += test_str # for display purpose only
        
        orca_dict = {0: [1024, 1000, 1024, 1000, 0, 1],
                     1: [1024, 1000, 1024, 1000, 0, 1],
                     2: [1024, 1000, 1024, 1000, 0, 1],
                     3: [1024, 1000, 1000, 1000, 0, 1],
                     4: [1024, 1000, 10, 10, 0, 1],
                     5: [5, 1, 1, 1, 0, 1]}
        tx_msg_02 = link.tx_obj(orca_dict, start_pos=send_size) - send_size
        send_size += tx_msg_02
        ic(tx_msg_01)
        ic(tx_msg_02) # want to see how many bytes a full pakage of orca_dict is
        ic(tx_msg_01*3 + tx_msg_02)
        
        link.send(send_size)
        
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
                    
        # Prase feedback from Arduino
        ## Prase string response
        rx_str = link.rx_obj(obj_type=type(test_str),
                             start_pos=0,
                             obj_byte_size=tx_msg_01 * 3)
        
        ## Prase dictionary response
        rx_dict = link.rx_obj(obj_type=type(orca_dict),
                              start_pos=int(tx_msg_01) * 3,
                              obj_byte_size=tx_msg_02,
                              list_format='i')
        
        
        # Display the received data
        print(f'\nSent: \n{sent_str} \n{orca_dict}')
        print()
        print(f'Recv: \n{rx_str} \n{rx_dict}')
    except KeyboardInterrupt:
        try:
            link.close()
        except:
            pass
    except:
        import traceback
        traceback.print_exc()
        try:
            link.close()
        except:
            pass