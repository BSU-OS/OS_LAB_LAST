import time

import win32com.client
import os
def write():
    qinfo=win32com.client.Dispatch("MSMQ.MSMQQueueInfo")
    computer_name = os.getenv('COMPUTERNAME')
    qinfo.FormatName="direct=os:"+computer_name+"\\PRIVATE$\\OutputQueue"
    queue=qinfo.Open(2,0)   # Open a ref to queue
    msg=win32com.client.Dispatch("MSMQ.MSMQMessage")
    msg.Label="Server"
    msg.Body = "Hi from server"
    msg.Send(queue)
    queue.Close()
def read():
    qinfo = win32com.client.Dispatch("MSMQ.MSMQQueueInfo")
    computer_name = os.getenv('COMPUTERNAME')
    qinfo.FormatName = "direct=os:" + computer_name + "\\PRIVATE$\\InputQueue"
    queue = qinfo.Open(1, 0)  # Open a ref to queue to read(1)
    msg = queue.Receive()
    print("Label:", msg.Label)
    print("Body :", msg.Body)
    # msg=win32com.client.Dispatch("MSMQ.MSMQMessage")
    # msg.Label="Client"
    # msg.Body = "Hi from client"
    # msg.Send(queue)
    queue.Close()
write()
read()
