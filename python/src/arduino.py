import time

class Arduino:
    def __init__(self, connection, bootMsg="boot"):
        self.connection = connection
        self.bootMsg = bootMsg
        self.connect()

    def format_msg(self, msg):
        msg = msg.decode()
        return msg.replace("\r\n","")

    def write_read(self, x):
        self.connection.write(bytes(x, 'utf-8'))
        time.sleep(1)
        data = self.connection.readline()
        return data

    def connect(self):
        response = ""
        while (not self.bootMsg in response):
            response = self.format_msg(self.connection.readline())
        print(response)

    def cmd_get_temp_humid(self):
        response = self.format_msg(self.write_read("temp_humid"))
        data = {}
        data["temperature"] = response.split(",")[0]
        data["humidity"] = response.split(",")[1]
        return data