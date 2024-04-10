# Starter code for assignment 3 in I/C/S 3/2 Programming with Software Libraries

# Replace the following placeholders with your information.

#Sam Pittman
#sfpittma@uci.edu
#59281059

import socket
from ds_protocol import turn_to_json, extract_json
import time

"""
checks the username, password, message, bio parameters given in send().
first checks that all parameter are strings.
then checks to make sure there aren't any spaces in username and password.
also checks that none of the parameters are blank.
if everything passes, a 1 is passed out of the function, causing the send function to activate the next step.
"""
def parameter_checker(username, password, message, bio):
  checkpoint = 0
  type_check = 0
  if bio == None:
    bio = "None"
  for item in [username, password, message, bio]:
    if type(item) != str:
      print(f"{item} is not a string. username, password, message, bio parameters must be strings.")
      type_check += 1
  if type_check == 0:
    if password.strip(" ") == "" or " " in password:
      print("ERROR! no white spaces allowed in password. no blank strings either")
      checkpoint += 1
    if username.strip(" ") == "" or " " in username:
      print("ERROR! no white spaces allowed in username. no blank strings either")
      checkpoint += 1
    if message == "":
      print("ERROR! no blank strings allowed for messages")
      checkpoint += 1
    if bio != "None":
      if bio == "":
        print("ERROR! no blank strings allowed for bio")
        checkpoint += 1
    if checkpoint == 0:
        checkpoint = 1
  return checkpoint

"""
connect is used to connect to the server using two parameters: server and port.
connect attempts to connect using the given information.
however, if an error occurs, the function will let them know.
if there is an error, connect returns false.
otherwise, connect returns the client so that it can be used in later functions of send. 
"""
def connect(server, port):
  try:
    client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client.settimeout(5)
    client.connect((server, port))

    print(f"client connected to {server} on {port}")

    return client
  # Makes sure the ip address is formatted correctly 
  except socket.gaierror:
    print("ERROR! did you correctly format the ip address?")
    return False
  # Makes sure the ip address and port are valid
  except ConnectionRefusedError:
    print("ERROR! the connection was refused. are the ip address and port valid?")
    return False
  # Waits 5 seconds for server connection. if nothing happens, the user is alerted that the connection was not possible
  except TimeoutError:
    print("ERROR! unable to connect to server")
    return False
  # Checks to make sure the user is connected to wifi
  except OSError:
    print("ERROR! network is unreachable. make sure you are  connected to wifi.")
    return False


"""
join is used to receive a token fromt the server. 
join takes three parameters: username, password, and client1.
client1 is the output of connect().
join takes a dictionary, populates it with the given username and password, calls on the json converter
from ds_protcol and sends the string to the server.
this string is then returned in dictionary form to be used for uploading a post or bio.
"""
def join(username, password, client1):
  initial_string = {"join": {"username": username,"password": password, "token":""}}
  json_string = turn_to_json(initial_string)

  send = client1.makefile('w')
  recv = client1.makefile('r')

  send.write(json_string + '\r\n')
  send.flush()

  resp = recv.readline()

  return extract_json(resp)

"""
upload_post has 3 parameters: message, token, and client2.
the token comes from the successful use of join() and client2 is the client from connect().
upload post populates a dictionary with given parameters, converts it to a json string, and sends it to the server.
"""
def upload_post(message, token, client2):
  upload_dict = {"token": token, "post": {"entry": message, "timestamp": time.time()}}
  json_string = turn_to_json(upload_dict)
  print(json_string)
  send = client2.makefile('w')
  recv = client2.makefile('r')

  send.write(json_string + '\r\n')
  send.flush()

  resp = recv.readline()

"""
upload_bio has 3 parameters: bio, token, and client3.
the token comes from the successful use of join() and client3 is the client from connect().
upload bio populates a dictionary with given parameters, converts it to a json string, and sends it to the server.
"""
def upload_bio(bio, token, client3):
  upload_string = {"token": token, "bio": {"entry": bio,"timestamp": time.time()}}
  json_string = turn_to_json(upload_string)

  send = client3.makefile('w')
  recv = client3.makefile('r')

  send.write(json_string + '\r\n')
  send.flush()

  resp = recv.readline()


'''
The send function joins a ds server and sends a message, bio, or both

:param server: The ip address for the ICS 32 DS server.
:param port: The port where the ICS 32 DS server is accepting connections.
:param username: The user name to be assigned to the message.
:param password: The password associated with the username.
:param message: The message to be sent to the server.
:param bio: Optional, a bio for the user.
'''
def send(server:str, port:int, username:str, password:str, message:str, bio:str=None):
  checkpoint = parameter_checker(username, password, message, bio)
  # If  checkpoint is 1, the function executes connect()
  if checkpoint == 1:
    new_client = connect(server,port)
    if new_client == False:
      # If new_client returns False, checkpoint remains at 1 and the flow does not continue
      checkpoint = 1
    else:
      checkpoint = 2
  # If checkpoint = 2, join is called upon
  if checkpoint == 2:
    response = join(username, password, new_client)
    print(response)
    # If the response is "error", the  user is alerted that there may be an issue with their password or username
    if response["response"]["type"] == "error":
      error_message = response["response"]["message"]
      print(f"Error! {error_message}")
    # If the response is "ok", the flow advances and the message and/or bio are uploaded
    if response["response"]["type"] == "ok":
      token = response["response"]["token"]
      # If no bio is given, bio is defaulted to none. Therefore this action only runs if no bio is given
      if bio == None:
        upload_post(message, token, new_client)
      # This action runs if send is activated in a3 and the user specifies they just want to upload a bio
      if message == "_-_":
        upload_bio(bio, token, new_client)
      # This action runs assuming that both the bio and message are given
      if bio != None:
        upload_post(message, token, new_client)
        upload_bio(bio, token, new_client)

