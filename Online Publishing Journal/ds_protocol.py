# ds_protocol.py

#Sam Pittman
#sfpittma@uci.edu
#59281059

import json
"""
calls the json.dumps function and converts the dictionary into a string
"""
def turn_to_json(json_msg:dict) -> str:
  try:
    dumped = json.dumps(json_msg)
    return dumped
  except:
    return None



"""
calls the json.loads function and converts the string into a dictionary
"""
def extract_json(json_msg:str) -> dict:
  try:
    json_obj = json.loads(json_msg)
    return json_obj
  except json.JSONDecodeError:
    print("Json cannot be decoded.")
    return False
