#!/bin/bash

source ./SystemLogs.sh

##################################   Network    ##################################
get_ip_addresses() 
{
    local command="Get IP Addresses"
    local shell_command="hostname -I; ip -6 addr | grep 'inet6'" #Defines the exact command that is executed.
    
    # Get IPv4 addresses
    ipv4_addresses=$(hostname -I | awk '{print "IPv4: " $1}')
    # Get IPv6 addresses
    ipv6_addresses=$(ip -6 addr | grep 'inet6' | awk '{print $2}')

    bold_blue="\e[1;34m"
    reset_color="\e[0m"

    local output="${bold_blue}IPv4 Addresses: $ipv4_addresses${reset_color}\n${bold_blue}IPv6 Addresses: $ipv6_addresses${reset_color}\n"
    
    echo -e "$output"
    log_command_output "$command" "$shell_command" "$output"
}

get_dns_servers() 
{
    local command="Get DNS Servers"
    local shell_command="grep '^nameserver' /etc/resolv.conf"
    
    dns_servers=$(grep '^nameserver' /etc/resolv.conf | awk '{print $2}')
    bold_blue="\e[1;34m"
    reset_color="\e[0m"
    
    local output="${bold_blue}DNS Servers: $dns_servers${reset_color}\n"
    
    echo -e "$output"
    log_command_output "$command" "$shell_command" "$output"
}

measure_speed() 
{
    local command="Measure Speed"
    local shell_command="speedtest-cli --simple"
    
    echo "Measuring download and upload speeds..."
    
    # Capture the speedtest output
    speedtest_output=$(speedtest-cli --simple)
    
    # Extract download and upload speeds
    download=$(echo "$speedtest_output" | grep 'Download' | awk '{print $2 " " $3}')
    upload=$(echo "$speedtest_output" | grep 'Upload' | awk '{print $2 " " $3}')
    
    # Define color codes
    bold_blue="\e[1;34m"
    reset_color="\e[0m"

    # Prepare the output
    local output="${bold_blue}Download Speed: $download${reset_color}\n${bold_blue}Upload Speed: $upload${reset_color}\n"
    
    # Print the output to the terminal
    echo -e "$output"
    
    # Log the command and its output
    log_command_output "$command" "$shell_command" "$output"
}


Network_MainLoop()
{
    # Device Main loop
    while true; 
    do
        echo "Menu:"
        echo "1) Show IP"
        echo "2) Show DNS"
        echo "3) Download & Upload Speed"
        echo "4) Exit"
        
        # Read user choice
        read -p "Enter your choice: " choice

        case $choice in
            1) get_ip_addresses ;;
            2) get_dns_servers ;;
            3) measure_speed ;;
            4) 
                log_command_output "Exit" "Exiting..."
                echo "Exiting..."
                break ;;
            *) 
                log_command_output "Invalid choice" "Invalid choice, try again."
                echo "Invalid choice, try again." ;;
        esac
    done
}
