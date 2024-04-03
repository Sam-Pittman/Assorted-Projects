# a3.py

# Starter code for assignment 3 in ICS 32 Programming with Software Libraries in Python

# Replace the following placeholders with your information.

#Sam Pittman
#sfpittma@uci.edu
#59281059
# import ds_client
# import ds_protocol
from Profile import Profile, Post
from pathlib import Path
from ds_client import send

"""
create() 
takes two parameters: a file location and a file name.
creates a file based off these two attributes. 
if file exists, the open_input() function is implemented and the file is opened.
if the file does not exist, it is created and given a Profile that is then filled with a password, username, bio, and server.
"""
def create(file_location, file_name):
    follow = Path(file_location) / (file_name + ".dsu")
    # If the file already exists, it is opened
    if Path(follow).exists():
        open_input(follow)
    # If the file does not exist, the file is insantiated with a new profile
    # The user is prompted to make a username, password, and bio for this new profile
    if not Path(follow).exists():
        follow.touch()
        f = Path(follow).open('r+')
        user_profile = Profile()
        initial_username = input("Create your username(no white spaces allowed):\n")
        while initial_username.strip(" ") == "" or " " in initial_username:
            print("ERROR! No white spaces allowed and no blank strings.")
            initial_username = input("Create your username(no white spaces allowed):\n")
        user_profile.username = initial_username
        initial_password = input("Create your password(no white spaces allowed):\n")
        while initial_password.strip(" ") == "" or " " in initial_password:
            print("ERROR! No white spaces allowed and no blank strings.")
            initial_password = input("Create your password(no white spaces allowed):\n")
        user_profile.password = initial_password
        initial_bio = input("Create your bio:\n")
        while initial_bio.strip(" ") == "":
            print("ERROR! No blank strings allowed")
            initial_bio = input("Create your bio:\n")
        user_profile.bio = initial_bio
        print("Please enter the IP address of the server in which you want to save this profile: ")
        specified_server = input()
        user_profile.dsuserver = specified_server
        user_profile.save_profile(Path(follow))
        f.close()
        # Once the file is created, it is passed into the open function
        open_input(follow)
"""
open_input()
takes on parameter, a file path, and opens that file if it exists. if the file does not exist, an error is given.
if the file does not have '.dsu', an error is given.
if the file exists, its profile is loaded onto the current path.
"""
def open_input(file_name):
    file = Path(file_name)
    # Makes sure the file exists
    while not file.exists():
        print('ERROR! FILE NOT FOUND')
        file_name = input()
        file = Path(file_name)
    # Makes sure the file is in a valid format
    while '.dsu' not in str(file):
        print('ERROR! INVALID FILE TYPE. MUST CONTAIN .DSU')
        file_name = input()
        file = Path(file_name)
    # If the file exists then it is populated with a Profile corresponding to this specific path
    if file.exists():
        f = file.open('r+')
        user_profile = Profile()
        user_profile.load_profile(Path(file))
        f.close()

"""
profile_interaction() has two parameters: option and path_of_file.
option is passed from the main body of user_interface and dictates whether the user wants to write a post or write a new bio.
the path is used to store that new message or new bio in the designated profile. 
"""
def profile_interaction(option, path_of_file):
    designated_profile = Profile()
    designated_profile.load_profile(Path(path_of_file))
    if option == 'P':
        post_1 = Post()
        new_post = input("Enter your new post:")
        # Makes sure the new message isn't a blank string.
        while new_post.strip(" ") == "":
            print("ERROR! No blank entries allowed")
            new_post = input("Enter your new post:")
        post_1.entry = new_post
        designated_profile.add_post(post_1)
    if option == 'B':
        new_bio = input("Enter the new bio:\n")
        # Makes sure the new bio isn't a blank string.
        while new_bio.strip(" ") == "":
            print("ERROR! No blank entries allowed")
            new_bio = input("Enter the new bio:\n")
        designated_profile.bio = new_bio
        print(f"Your new bio is {new_bio}")  

    designated_profile.save_profile(path_of_file)
"""
user_interface is the main function of a3.
it first asks a user whether they want to create or load a profile.
then they are prompted to write a new post or a new bio.
after that they can either upload something to the server or not. 
depending on what they decide to upload, the send function from ds_client is called and their message and/or is uploaded
"""
def user_interface():
    print("Hi! Welcome to Sam's Online Journal")
    print("Would you like to create(C) a new profile or log(L) into an existing profile?")
    create_or_load = input()
    while create_or_load not in ['C','L']:
        print("Error! Invalid Command")
        print("Would you like to create(C) a new profile or log(L) into an existing profile?")
        create_or_load = input()
    # If the user opts to crate a profile, they are asked for a name and a path and then create() is launched
    if create_or_load == "C":
        print("Great! What is the name of the file that you would like to create?")
        name = input()
        # Makes sure the file name isn't a blank string
        while name.strip(" ") == "":
            print("Please enter valid file name")
            name = input()
        print("And where would you like to store it?")
        location = input()
        # Makes sure the path exists
        while not Path(location).exists():
            print('ERROR: Path of file does not exist')
            print("Where would you like to store it?")
            location = input()
        create(location,name)
        file_path = f"{location}/{name}.dsu"

    # Asks the user for the file they want to open and passes it into the open_input() function
    if create_or_load == "L":
        print("Great! Please give the path of the file you would like to open.")
        choice = input()
        file_path = choice
    # Once the profile is created or loaded, the user can write a new post or a new bio
    print("Now that your profile is loaded, would you like to write a post(P) or write a new bio(B)?")
    post_or_bio = input()
    # Makes sure the comman is valid
    while post_or_bio not in ['P','B']:
        print("Error! Invalid Command")
        print("Would you like to write a post(P) or write a new bio(B)?")
        post_or_bio = input()
    # Passes the user's choice into profile_interaction
    profile_interaction(post_or_bio,file_path)
    print("now that you've written your post or bio, would you like to post something online?(yes or no)")
    yes_or_no = input()
    while yes_or_no not in ['yes','no']:
        print("Error! Invalid Command")
        print("Would you like to post online?(yes or no)")
        yes_or_no = input()
    # If the user wants to upload something, they are asked whether they want to upload one of their posts or their bio
    if yes_or_no == 'yes':
        designated_profile = Profile()
        designated_profile.load_profile(Path(file_path))
        print("Okay! Would you like to upload your bio(B) or a post?(P)")
        upload = input()
        while upload not in ['P','B']:
            print("Error! Invalid Command")
            print("Would you like to upload your bio(B) or a post?(P)")
            upload = input()
        if upload == "P":
            # Makes sure there are posts to upload
            if len(designated_profile.get_posts()) == 0:
                print("There are no posts to print. Please create a post first")
            if len(designated_profile.get_posts()) > 0:
                post_to_print = input("Enter the ID of the post you want to print:")
                valid_index = False
                while valid_index == False:
                    try:
                        int(post_to_print)
                        post_to_print = designated_profile.get_posts()[int(post_to_print)]
                        valid_index = True
                    except ValueError:
                        print("Please enter a valid integer")
                        valid_index = False
                        post_to_print = input("Enter the ID of the post you want to print:")
                    except IndexError:
                        print("Post not found. Index out of range")
                        valid_index = False
                        post_to_print = input("Enter the ID of the post you want to print:")
                # After all errors are accounted for, their message is passed into the send function and uploaded to the server
                send(designated_profile.dsuserver, 3021, designated_profile.username, designated_profile.password, post_to_print['entry'])
        if upload == "B":
            # If they simply want to upload their bio, the send function is called upon with the designated bio
            print("Great! Your bio has been uploaded to the website")
            send(designated_profile.dsuserver, 3021, designated_profile.username, designated_profile.password, "_-_", designated_profile.bio)
    if yes_or_no == 'no':   
        print("Okay! Have a great day!")
user_interface()
