# ui.py


#Sam Pittman
#sfpittma@uci.edu
#59281059

from pathlib import Path
from Profile import Profile, Post

"""
create() 
takes two parameters: a file location and a file name.
creates a file based off these two attributes. 
if file exists, the open_input() function is implemented and the file is opened.
if the file does not exist, it is created and given a Profile that is then filled with a password, username, and bio.
"""
def create(file_location, file_name):
    follow = Path(file_location) / (file_name + ".dsu")
    if Path(follow).exists():
        open_input(follow)

    # If the file does not exist, the file is insantiated with a new profile
    # The user is prompted to make a username, password, and bio for this new profile
    if not Path(follow).exists():
        follow.touch()
        f = Path(follow).open('r+')
        user_profile = Profile()
        initial_username = input("Create your username(no white spaces allowed):\n")
        while initial_username.strip(" ") == "":
            print("ERROR! No white spaces allowed")
            initial_username = input("Create your username(no white spaces allowed):\n")
        user_profile.username = initial_username
        initial_password = input("Create your password(no white spaces allowed):\n")
        while initial_password.strip(" ") == "":
            print("ERROR! No white spaces allowed")
            initial_password = input("Create your password(no white spaces allowed):\n")
        user_profile.password = initial_password
        initial_bio = input("Create your bio:\n")
        while initial_bio.strip(" ") == "":
            print("ERROR! No white spaces allowed")
            initial_bio = input("Create your bio:\n")
        user_profile.bio = initial_bio
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
edit_file()
Takes in a command, a Profile to edit, and a path as parameters. 
Profile is altered depending on the given command and certain errors (i.e. white space, and invalid IDs) and accounted for.
at the end of the function, the profile is saved back to the path.
"""
def edit_file(command, designated_profile, path_of_file):
    # Loads the current Profile
    designated_profile = Profile()
    designated_profile.load_profile(Path(path_of_file))


    # Adjusts the username
    # Makes sure there are no blank spaces and the username is not an empty string
    if command == '-usr':
        new_username = input("Enter the new username(no white spaces allowed):\n")
        while " " in new_username or new_username.strip(" ") == "":
            print("ERROR! No white spaces allowed. No blank strings either")
            new_username = input("Enter the new username(no white spaces allowed):\n")
        designated_profile.username = new_username
        print(f"Your new username is {new_username}")


    # Adjusts the password
    # Makes sure there are no blank spaces and the password is not an empty string
    if command == '-pwd':
        new_password = input("Enter the new password(no white spaces allowed):\n")
        while " " in new_password or new_password.strip(" ") == "":
            print("ERROR! No white spaces allowed. No blank entries either.")
            new_password = input("Enter the new password(no white spaces allowed):\n")
        designated_profile.password = new_password
        print(f"Your new password is {new_password}")


    # Adjusts the bio
    # Makes sure there are no blank spaces and the bio is not an empty string
    if command == '-bio':
        new_bio = input("Enter the new bio:\n")
        while new_bio.strip(" ") == "":
            print("ERROR! No blank entries allowed")
            new_bio = input("Enter the new bio:\n")
        designated_profile.bio = new_bio
        print(f"Your new bio is {new_bio}")  


    # Creates a new post using the Post class
    # Makes sure the new post is not an empty string
    if command == '-addpost':
        post_1 = Post()
        new_post = input("Enter your new post:")
        while new_post.strip(" ") == "":
            print("ERROR! No blank entries allowed")
            new_post = input("Enter your new post:")
        post_1.entry = new_post
        designated_profile.add_post(post_1)


    # Deletes a post but only if there are posts to delete
    # Makes sure the post exists and the ID given by the user is a valid integer
    if command == '-delpost':
        if len(designated_profile.get_posts()) == 0:
            print("There are no posts to delete. Please create a post first")
        if len(designated_profile.get_posts()) > 0:
            post_to_delete = input("Enter the ID of the post you want to delete:")
            valid_integer = False
            while valid_integer == False:
                try:
                    int(post_to_delete)
                    post_deleted = designated_profile.del_post(int(post_to_delete))
                    while post_deleted == False:
                        print("Index out of range. Enter valid ID")
                        post_to_delete = input("Enter the ID of the post you want to delete:")
                        post_deleted = designated_profile.del_post(int(post_to_delete))
                    valid_integer = True
                except ValueError:
                    print("Please enter a valid integer")
                    valid_integer = False
                    post_to_delete = input("Enter the ID of the post you want to delete:")
            if valid_integer == True:
                print("Post Deleted")
    # Saves the profile with current adjustments
    designated_profile.save_profile(path_of_file)
"""
retrieve_from_file()
Takes in a command, a Profile to retrieve data from, and a path as parameters. 
Depending on the user command, corresponding data is printed out
"""
def retrieve_from_file(command, designated_profile, path_of_file):
    # Loads the current Profile
    designated_profile = Profile()
    designated_profile.load_profile(Path(path_of_file))

    # Prints username
    if command == '-usr':
        print("The username is:")
        print(designated_profile.username)

    # Prints password
    if command == '-pwd':
        print("The password is:")
        print(designated_profile.password)

    # Prints bio
    if command == '-bio':
        print("The bio is:")
        print(designated_profile.bio)

    # Prints all the posts but only if there are posts to print
    if command == '-posts':
        if len(designated_profile.get_posts()) == 0:
            print("There are no posts to print. Please create a post first")
        if len(designated_profile.get_posts()) > 0:
            for i in designated_profile.get_posts():
                print(i)

    # Prints a post but makes sure there are posts to print
    # Also makes sure the ID of the post is valid
    if command == '-post':
        if len(designated_profile.get_posts()) == 0:
            print("There are no posts to print. Please create a post first")
        if len(designated_profile.get_posts()) > 0:
            post_to_print = input("Enter the ID of the post you want to print:")
            valid_index = False
            while valid_index == False:
                try:
                    int(post_to_print)
                    print(designated_profile.get_posts()[int(post_to_print)])
                    valid_index = True
                except ValueError:
                    print("Please enter a valid integer")
                    valid_index = False
                    post_to_print = input("Enter the ID of the post you want to print:")
                except IndexError:
                    print("Post not found. Index out of range")
                    valid_index = False
                    post_to_print = input("Enter the ID of the post you want to print:")

    # Prints all contents of the file's Profile
    if command == '-all':
        print(f'Username: {designated_profile.username}')
        print(f'Password: {designated_profile.password}')
        print(f'Bio: {designated_profile.bio}')
        print('Posts: ')
        for i in designated_profile.get_posts():
            print(i)




"""
edit_or_retrieve_admin()
is a function exclusively used in ADMIN mode
it takes one parameter, a profile_path, and lets the administrator edit or print out data from the profile correlating to the path.
"""
def edit_or_retrieve_admin(profile_path):
    # Loads the current Profile
    designated_profile = Profile()
    designated_profile.load_profile(Path(profile_path))


    e_or_p = input()
    # Makes sure the entered command isn't blank
    while  e_or_p.strip(" ") == "":
        print("ERROR. COMMAND CANNOT BE BLANK")
        e_or_p = input()
    while e_or_p[0] != 'Q':
        while e_or_p[0] not in ['E', 'P']:
            print("INVALID COMMAND. Enter E  for edit. Enter P for print")
            e_or_p = input()



        if e_or_p[0] == 'E':
            # Counts the number of commands in the line
            edit_commands = ['-usr','-pwd','-bio','-addpost','-delpost']
            command_count = 0
            for i in edit_commands:
                if i in e_or_p:
                    command_count += 1

            # Allows adjustments to the username to be made
            if '-usr' in e_or_p:
                specified_command = e_or_p.index('-usr')
                change_beginning = specified_command + 5
                place_holder = e_or_p[change_beginning:]
                try:
                    change_end = place_holder.index('-') -1 
                except ValueError:
                    change_end = -1
                # Strips the username of quotes and makes sure the username isn't blank
                change = place_holder[:change_end] 
                change = change.replace('"',"")
                change = change.replace("'","")
                if " " in change:
                    print('ERROR! NO WHITE SPACES ALLOWED IN USERNAME')
                if change.strip(" ") == "":
                    print('ERROR! NO BLANK ENTRIES ALLOWED')
                else:
                    designated_profile.username = change

            # Allows adjustments to the password to be made
            if '-pwd' in e_or_p:
                specified_command = e_or_p.index('-pwd')
                change_beginning = specified_command + 5
                place_holder = e_or_p[change_beginning:]
                try:
                    change_end = place_holder.index('-') -1
                except ValueError:
                    change_end = -1
                # Strips the username of quotes and makes sure the username isn't blank
                change = place_holder[:change_end]
                change = change.replace('"',"")
                change = change.replace("'","")
                if " " in change:
                    print('ERROR! NO WHITE SPACES ALLOWED IN PASSWORD')
                if change.strip(" ") == "":
                    print('ERROR! NO BLANK ENTRIES ALLOWED')
                else:
                    designated_profile.password = change

            # Allows adjustments to the bio to be made
            if '-bio' in e_or_p:
                specified_command = e_or_p.index('-bio')
                change_beginning = specified_command + 5
                place_holder = e_or_p[change_beginning:]
                try:
                    change_end = place_holder.index('-')
                except ValueError:
                    change_end = -1
                # Strips the username of quotes and makes sure the bio isn't blank
                change = place_holder[:change_end]
                change = change.replace('"',"")
                change = change.replace("'","")
                if change.strip(" ") == "":
                    print('ERROR! NO BLANK ENTRIES ALLOWED')
                else:
                    designated_profile.bio = change

            # Allows for a post to be added
            if '-addpost' in e_or_p:
                specified_command = e_or_p.index('-addpost')
                change_beginning = specified_command + 9
                place_holder = e_or_p[change_beginning:]
                try:
                    change_end = place_holder.index('-')
                except ValueError:
                    change_end = -1
                # Strips the username of quotes and makes sure the new post isn't blank
                change = place_holder[:change_end]
                change = change.replace('"',"")
                change = change.replace("'","")
                if change.strip(" ") == "":
                    print('ERROR! NO BLANK ENTRIES ALLOWED')
                else:
                    change = Post()
                    designated_profile.add_post = change

            # Allows a post to be deleted
            if '-delpost' in e_or_p:
                specified_command = e_or_p.index('-delpost')
                id = e_or_p[specified_command + 9]
                if id.strip == "":
                    print("please enter a valid ID of the post you want to delete")
                # Makes sure there are posts to delete
                else:
                    if len(designated_profile.get_posts()) == 0:
                        print("There are no posts to delete. Please create a post first")
                    if len(designated_profile.get_posts()) > 0:
                        # Makes sure the ID given is valid
                        try:
                            int(id)
                        except ValueError:
                            print("Please enter a valid integer for ID")
                        post_deleted = designated_profile.del_post(int(id))
                        if post_deleted == False:
                            print("Index out of range. Enter valid ID")
            # If there are no commands, an error is raised
            if command_count == 0:
                print("Invalid! No Edit Command given")
            designated_profile.save_profile(profile_path)
            e_or_p = input()



        if e_or_p[0] == 'P':
            print_commands = ['-usr','-pwd','-bio','-posts','-post','all']
            # Counts the number of commands in the line
            command_count = 0
            for i in print_commands:
                if i in e_or_p:
                    command_count += 1
            # Prints the username
            if '-usr' in e_or_p:
                print("The username is:")
                print(designated_profile.username)
            # Prints the password
            if '-pwd' in e_or_p:
                print("The password is:")
                print(designated_profile.password)
            # Prints the bio
            if '-bio' in e_or_p:
                print("The bio is:")
                print(designated_profile.bio)
            # Prints all posts
            if '-posts' in e_or_p:
                if len(designated_profile.get_posts()) == 0:
                    print("There are no posts to print. Please create a post first")
                if len(designated_profile.get_posts()) > 0:
                    for i in designated_profile.get_posts():
                        print(i)
            # Prints a post only if the ID given is valid
            if '-post' in e_or_p:
                if len(designated_profile.get_posts()) == 0:
                    print("There are no posts to print. Please create a post first")
                if len(designated_profile.get_posts()) > 0:
                    post_to_print = input("Enter the ID of the post you want to print:")
                    valid_index = False
                    while valid_index == False:
                        try:
                            int(post_to_print)
                            print(designated_profile.get_posts()[int(post_to_print)])
                            valid_index = True
                        except ValueError:
                            print("Please enter a valid integer")
                            valid_index = False
                            post_to_print = input("Enter the ID of the post you want to print:")
                        except IndexError:
                            print("Post not found. Index out of range")
                            valid_index = False
                            post_to_print = input("Enter the ID of the post you want to print:")
            # Prints all the contents of the current Profile
            if '-all' in e_or_p:
                print(f'Username: {designated_profile.username}')
                print(f'Password: {designated_profile.password}')
                print(f'Bio: {designated_profile.bio}')
                print('Posts: ')
                for i in designated_profile.get_posts():
                    print(i)
            # If there are no commands, an error is raised
            if command_count == 0:
                print('Invalid Print Command')
            e_or_p = input()


"""
create_admin()
is exclusively used in ADMIN mode.
It takes a single command line and converts it to a file. 
However, it makes sure that '-n' is present, as well as a valid path and file name.
If the ADMIN attempts to create a new file that already exists, the file is simply opened.
"""
def create_admin(user_command):
    valid_creation = False
    while valid_creation == False:
        if user_command == 'C':
            print('ERROR \n Invalid Input.')
        else: 
            # Makes sure -n is present in the admin's input
            if ('-') not in user_command:
                print("Please enter -n and specify the name of the file")
            elif '-n' not in user_command:
                print("Please enter -n and specify the name of the file")
            elif '-n' in user_command:
                dash = user_command.index('-n')
                user_input = user_command[2:dash - 1]
                try:
                    # If the formatting is valid, the file is created
                    follow = Path(user_input)
                    file_name = user_command[dash + 3:]
                    if file_name.strip(' ') == "":
                        print("Please enter valid file name")
                    else:
                        follow = follow / (file_name + ".dsu")
                        # If the file exists, then it is passed into the open function
                        if follow.exists():
                            open_input_admin(f"O {follow}")
                        # Creates file if it does not exist
                        if not follow.exists():
                            follow.touch()
                        # Opens the file and instantiates it with a new profile
                        f = Path(follow).open('r+')
                        user_profile = Profile()
                        user_profile.save_profile(Path(follow))
                        f.close()
                        edit_or_retrieve_admin(follow)
                        valid_creation = True
                except FileNotFoundError:
                    print("No such file or directory! Please enter a valid file or directory")
        user_command = input()


"""
open_input_admin()
is exclusively used in ADMIN mode.
It takes a single command line.
It opens a file and makes sure that a valid file path is given.
"""
def open_input_admin(user_command):
    # Makes sure the inputted file name isn't blank or an empty string
    if user_command.strip(" ") == "":
        print('ERROR: COMMAND CANNOT BE BLANK')
        user_command = input()
    if user_command.strip(' ') == 'O':
        print('ERROR: FILE MUST BE SPECIFIED')
        user_command = input()
    else:
        file_name = str(user_command)[2:]
        file = Path(file_name)
        # Checks to see if the file exists
        if not file.exists():
            print('ERROR! FILE NOT FOUND')
            user_command = input()
        # Checks if the file is in .dsu format
        elif '.dsu' not in str(file):
            print('ERROR! INVALID FILE TYPE')
            user_command = input()
        # If the file exists then it is instaniated with profile that corresponds to the current path
        elif file.exists():
            f = file.open('r+')
            user_profile = Profile()
            user_profile.load_profile(file_name)
            f.close()
            edit_or_retrieve_admin(file_name)



"""
file_interaction_admin()
a function that is launched upon entering ADMIN mode.
the first decision the administrator must make is to open or create a file.
"""
def file_interaction_admin(user_command):
    while  user_command.strip(" ") == "":
        print("ERROR. COMMAND CANNOT BE BLANK")
        user_command = input()
    while user_command[0] != 'Q ':
        new_command = user_command.split(' ')
        if new_command[0]  not in ['O','C']:
            print("Please enter a valid Command")
            user_command = input()
        if new_command[0] in ['O','C']:
            if user_command[0] == 'C':
                create_admin(user_command)
                user_command = input()
            if user_command[0] == 'O':
                open_input_admin(user_command)
