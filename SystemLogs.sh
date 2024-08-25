#!/bin/bash

MonitorLogs() {
    sudo dmesg --follow
}

CreateFile() {
    # Define the log file path
    LOGFILE=~/Desktop/logfile_$(date +'%Y-%m-%d').log

    # Check if the file already exists
    if [ ! -f "$LOGFILE" ]; then
        # Create the file
        touch "$LOGFILE"
        echo "$(date +'%Y-%m-%d %H:%M:%S') - Log file created: $LOGFILE" >> "$LOGFILE"
    else
        echo "$(date +'%Y-%m-%d %H:%M:%S') - Log file already exists: $LOGFILE" >> "$LOGFILE"
    fi

    # Set permissions
    sudo chmod 666 "$LOGFILE"
}

# Function to remove color escape sequences
strip_color_codes() {
    echo -e "$1" | sed 's/\x1B\[[0-9;]*[mK]//g'
}

log_command_output() {
    local description="$1"
    local shell_command="$2"
    
    # Execute the command and capture the output
    local output
    output=$(eval "$shell_command")

    # Strip color codes from the output before logging
    local plain_output
    plain_output=$(strip_color_codes "$output")
    
    # Log the description, shell command, and its output to the log file
    echo "$(date): Executed - $description" | tee -a "$LOGFILE"
    echo "Command: $shell_command" | tee -a "$LOGFILE"
    echo -e "$plain_output" | tee -a "$LOGFILE"
    echo "" | tee -a "$LOGFILE"  # Add a blank line for readability
}
