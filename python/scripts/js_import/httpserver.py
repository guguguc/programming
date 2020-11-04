from flask import Flask, Response

server = Flask(__name__)
server.debug = True

@server.route('/<path:subpath>')
    return server.send_static_file(subpath)
def echo(subpath):
   
server.run()