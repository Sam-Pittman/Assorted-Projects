# a2.py

#Sam Pittman
#sfpittma@uci.edu
#59281059
from pathlib import Path
from ui import create, open_input, file_interaction_admin, edit_file, retrieve_from_file
"""
user_interace()
a function that is meant to be user friendly.
first prompts the user to create or open a file.
it then calls on the two create and open functions in ui.py and returns a path.
this path is passed into the next option: edit or print.
until the user enters Q, the user will be prompted to edit or print different parts of a file's profile.
"""
def user_interface():
    print("Welcome to Sam's File Interactive")
    print("what would you like to do? create ('C') or open ('O') a file?")
    create_or_open = input()
    while create_or_open not in ['C','O','Q','admin']:
        print('ERROR! Invalid Input')
        print("what would you like to do? create ('C') or open ('O') a file?")
        create_or_open = input()

    # Asks the user for a file name to create
    # Makes sure the file name is valid
    # Asks for a path to store the file and makes sure the path is valid
    # Passes the file name and location into the create() function and outputs a generated profile to be used later in the Edit or Print area
    if create_or_open == "C":
        print("Great! What is the name of the file that you would like to create?")
        name = input()
        while name.strip(" ") == "":
            print("Please enter valid file name")
            name = input()
        print("And where would you like to store it?")
        location = input()
        while not Path(location).exists():
            print('ERROR: Path of file does not exist')
            print("Where would you like to store it?")
            location = input()
        generated_profile = create(location,name)
        file_path = f"{location}/{name}.dsu"

    # Asks the user for the file they want to open and passes it into the open_input() function
    if create_or_open == "O":
        print("Great! Please give the path of the file you would like to open.")
        choice = input()
        generated_profile = open_input(choice)
        file_path = choice

    # If the user enters 'admin', the file_interaction_admin() function is called upon
    if create_or_open == 'admin':
        print('Administrator Access Granted')
        user_command = input()
        file_interaction_admin(user_command)
    


    # If the user used C or O, the user is prompted with options for editing or printing
    print("What would you like to do with this file? Edit(E) or Print(P) Data?(Q to quit)")
    edit_retrieve =  input()
    # Makes sure the user enters a valid command
    while edit_retrieve not in ['E', 'P', 'Q']:
        print("ERROR! INVALID COMMAND")
        print("What would you like to do with this file? Edit(E) or Print(P) Data?(Q to quit)")
        edit_retrieve =  input()

    # Asks the user for input until they enter Q
    while edit_retrieve != 'Q':
        if edit_retrieve == 'Q':
            break

        # If the user chooses to edit, they are given multiple options that correspond to commands
        # These commands are passed into the edit function in ui.py along with a generate profile and the file path
        if edit_retrieve == 'E':
            print("Which would you like to do? \n1. Edit Username \n2. Edit Password\n3. Edit Bio\n4. Add post\n5. Delete post")
            edit_command = input()
            # Makes sure the command is valid
            while edit_command not in ['1','2','3','4','5']:
                print('ERROR! Invalid Command(please enter a digit corresonding to the desired option')
                print("Which would you like to do? \n1. Edit Username \n2. Edit Password\n3. Edit Bio\n4. Add post\n5. Delete post")
                edit_command = input()
            if edit_command == '1':
                edit_file('-usr', generated_profile, file_path)
            if edit_command == '2':
                edit_file('-pwd', generated_profile, file_path)
            if edit_command == '3':
                edit_file('-bio', generated_profile, file_path)
            if edit_command == '4':
                edit_file('-addpost', generated_profile, file_path)
            if edit_command == '5':
                edit_file('-delpost', generated_profile, file_path)


        # If the user requests to print something, they are prompted with different options to print data from the file
        # The commands are passed into the retrieve_from_file() function from ui.py along with a generate profile and the file path
        if edit_retrieve == 'P':
            print("Which would you like to do? \n1. Print Username \n2. Print Password\n3. Print Bio\n4. Print all posts\n5. Print a post by ID\n6. Print all file contents")
            retrieve_command = input()
            # Makes sure the command is valid
            while retrieve_command not in ['1','2','3','4','5','6']:
                print('ERROR! Invalid Command(please enter a digit corresonding to the desired option)')
                print("Which would you like to do? \n1. Print Username \n2. Print Password\n3. Print Bio\n4. Print all posts\n5. Print a post by ID\n6. Print all file contents")
                retrieve_command = input()
            if retrieve_command == '1':
                retrieve_from_file('-usr', generated_profile, file_path)
            if retrieve_command == '2':
                retrieve_from_file('-pwd', generated_profile, file_path)
            if retrieve_command == '3':
                retrieve_from_file('-bio', generated_profile, file_path)
            if retrieve_command == '4':
                retrieve_from_file('-posts', generated_profile, file_path)
            if retrieve_command == '5':
                retrieve_from_file('-post', generated_profile, file_path)
            if retrieve_command == '6':
                retrieve_from_file('-all', generated_profile, file_path)
        print("What would you like to do with this file? Edit(E) or Print(P) Data?(Q to quit)")
        edit_retrieve =  input()
user_interface()