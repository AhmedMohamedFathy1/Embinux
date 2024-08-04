#!/usr/bin/python3

import tkinter as tk
from tkinter import messagebox

# Function to update dictionary with data from entry fields
def update_dictionary():
    # Collect data from entry fields'
    key = ["Name","ID","Depertamnet","Salary","Password","DOA"]
    value = [0,0,0,0,0,0]

    value[0] = entry_value1.get()
    value[1] = entry_value2.get()
    value[2] = entry_value3.get()
    value[3] = entry_value4.get()
    value[4] = entry_value5.get()
    value[5] = entry_value6.get()
    
    # Check if all entries are filled
    for  ValueIndex in value:
        i=0
        data_dict[i] = ValueIndex
        i+=1
        # Display updated dictionary
        print(data_dict)
    

# Initial dictionary
data_dict = {}

# Setting up the GUI
root = tk.Tk()
root.title("Data Entry")
# Set geometry(width height)
root.geometry('350x400')

# Create entry fields for multiple key-value pairs
#Name Data Entery
tk.Label(root, text="Name").grid(row=0, column=0, padx=10, pady=5)
entry_key1 = tk.Label(root)
entry_key1.grid(row=0, column=1, padx=10, pady=5)

tk.Label(root).grid(row=0, column=0, padx=10, pady=5)
entry_value1 = tk.Entry(root)
entry_value1.grid(row=0, column=1, padx=10, pady=5)


#ID Data Entery
tk.Label(root, text="ID:").grid(row=1, column=0, padx=10, pady=5)
entry_key2 = tk.Label(root)
entry_key2.grid(row=1, column=1, padx=10, pady=5)

tk.Label(root).grid(row=1, column=0, padx=10, pady=5)
entry_value2 = tk.Entry(root)
entry_value2.grid(row=1, column=1, padx=10, pady=5)

#Department Data Entery
tk.Label(root, text="Department:").grid(row=2, column=0, padx=10, pady=5)
entry_key3 = tk.Label(root)
entry_key3.grid(row=2, column=1, padx=10, pady=5)

tk.Label(root).grid(row=2, column=0, padx=10, pady=5)
entry_value3 = tk.Entry(root)
entry_value3.grid(row=2, column=1, padx=10, pady=5)

#Salary Data Entery
tk.Label(root, text="Salary:").grid(row=3, column=0, padx=10, pady=5)
entry_key4 = tk.Label(root)
entry_key4.grid(row=3, column=1, padx=10, pady=5)

tk.Label(root).grid(row=3, column=0, padx=10, pady=5)
entry_value4 = tk.Entry(root)
entry_value4.grid(row=3, column=1, padx=10, pady=5)

#Password Data Entery
tk.Label(root, text="Password:").grid(row=4, column=0, padx=10, pady=5)
entry_key5 = tk.Label(root)
entry_key5.grid(row=4, column=1, padx=10, pady=5)

tk.Label(root).grid(row=4, column=0, padx=10, pady=5)
entry_value5 = tk.Entry(root)
entry_value5.grid(row=4, column=1, padx=10, pady=5)

#Days of Absence Data Entery
tk.Label(root, text="Days of Absence:").grid(row=5, column=0, padx=10, pady=5)
entry_key6 = tk.Label(root)
entry_key6.grid(row=5, column=1, padx=10, pady=5)

tk.Label(root).grid(row=5, column=0, padx=10, pady=5)
entry_value6 = tk.Entry(root)
entry_value6.grid(row=5,column=1, padx=10, pady=5)


# Button to update the dictionary with data from entry fields
update_button = tk.Button(root, text="Update Dictionary", command=update_dictionary)
update_button.grid(row=7, columnspan=2, pady=10)

# Start the GUI event loop
root.mainloop()
