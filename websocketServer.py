import tornado.httpserver  
  
import tornado.ioloop  
import tornado.options  
import tornado.web  
import tornado.websocket  
  
from tornado.options import define, options  
  
define("port", default=8888, help="run on the given port", type=int)  
  
class EchoWebSocket(tornado.websocket.WebSocketHandler):
    def open(self):  
        print "WebSocket opened"  
        
    def on_message(self, message):  
        if message == "start":
            f = open("/tmp/ECGFromServer", "w")
            f.write("s")
            f.close()
            f = open("/tmp/ECGToServer", "r")
            line = f.readline()
            id = int(line)
            self.write_message(u"ID: " +str(id))  
        else:
            f = open("/tmp/ECGFromServer", "w")
            f.write(message)
            f.close()
            f = open("/tmp/ECGToServer" + message, "r")
            data = "dane:\n";
            while True:
                line = f.readline()
                if len(line) == 0:
                    break # eof
                data += line + "\n";
            self.write_message(data)
                    
    def on_close(self):  
        print "WebSocket closed"  

def startTornado():
    tornado.options.parse_command_line()  
    application = tornado.web.Application([  
        (r"/", EchoWebSocket),  
        ])  
    http_server = tornado.httpserver.HTTPServer(application)  
    http_server.listen(options.port)
    tornado.ioloop.IOLoop.instance().start()  

def stopTornado():
    tornado.ioloop.IOLoop.instance().stop()
                             
def main():  
    import threading
    threading.Thread(target=startTornado).start()
    f = open("/tmp/ECGToServerClose", "r")
    f.close()
    stopTornado()
                                        
                                      
if __name__ == "__main__":  
    main()  
