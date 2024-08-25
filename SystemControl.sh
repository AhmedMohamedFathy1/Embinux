#!/bin/bash

##################################   System Control    ##################################

source ./SystemLogs.sh

# Bold red color for system control messages
bold_red="\e[1;31m"
# Reset color
reset_color="\e[0m"

log_command_output() {
    local description="$1"
    local shell_command="$2"
    local output="$3"
    
    # Strip color codes from the output before logging
    local plain_output=$(echo -e "$output" | sed 's/\x1B\[[0-9;]*[mK]//g')
    
    # Log the description, shell command, and its output to the log file
    echo "$(date): Executed - $description" | tee -a "$log_file"
    echo "Command: $shell_command" | tee -a "$log_file"
    echo -e "$plain_output" | tee -a "$log_file"
    echo "" | tee -a "$log_file"  # Add a blank line for readability
}

# Function to reboot the system
reboot_system() 
{
    local command="Reboot System"
    local shell_command="sudo reboot"

    echo -e "${bold_red}Rebooting the system...${reset_color}"
    
    log_command_output "$command" "$shell_command" "Rebooting the system..."
    
    sudo reboot
}

# Function to shut down the system
shutdown_system() 
{
    local command="Shutdown System"
    local shell_command="sudo shutdown -h now"

    echo -e "${bold_red}Shutting down the system...${reset_color}"
    
    log_command_output "$command" "$shell_command" "Shutting down the system..."
    
    sudo shutdown -h now
}

# Main menu function
SystemControl_MainLoop()
{
    while true; do
        echo "System Control Menu:"
        echo "1) Reboot System"
        echo "2) Shutdown System"
        echo "3) Exit"

        read -p "Enter your choice: " choice

        case $choice in
            1)
                reboot_system
                ;;
            2)
                shutdown_system
                ;;
            3)
                echo "Exiting..."
                log_command_output "Exit" "None" "Exiting..."
                break
                ;;
            *)
                echo "Invalid choice, try again."
                log_command_output "Invalid Choice" "None" "Invalid choice, try again."
                ;;
        esac
    done
}
