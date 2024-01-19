import time
import numpy as np
from pySerialTransfer import pySerialTransfer as txfer
from icecream import ic

#DEBUG
# print("Received cmd:")
# print("Robot ID = ", robo_id)
# print("v_x = ", posx)
# print("v_y = ", posy)
# print("Angular velocity = ", ang_v)
# print("Kick = ", active_kick)

if __name__ == '__main__':
    # Initialize the serial transfer object
    link = txfer.SerialTransfer('COM4')
    try:
        # Open the serial port
        link.open()
        time.sleep(2)  # wait for Arduino to reset ###########################

        # Send "hello arduino"
        send_str = "hello arduino"
        link.tx_obj(send_str)
        link.send(len(send_str))

        while not link.available():
            # Wait for response
            time.sleep(0.01)

        # Receive acknowledgement
        received_str = link.rx_obj(obj_type=type(''), obj_byte_size=link.bytesRead)
        print(f"Received: {received_str}")
    
    except KeyboardInterrupt:
        print('Interrupted by user')
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

    
    
        
