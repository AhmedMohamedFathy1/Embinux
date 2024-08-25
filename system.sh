#!/bin/bash

source ./SystemLogs.sh
# Bold blue color
bold_blue="\e[1;34m"
# Reset color
reset_color="\e[0m"

Show_CPU_Usage() {
    local command="Show CPU Usage"
    local shell_command="grep 'cpu ' /proc/stat; sleep 1; grep 'cpu ' /proc/stat"
    
    echo "***********   CPU Usage Info   ***********"
    
    # Initial CPU stats
    cpu_stats_start=$(grep 'cpu ' /proc/stat)
    
    # Wait for a short interval
    sleep 1
    
    # Second CPU stats
    cpu_stats_end=$(grep 'cpu ' /proc/stat)
    
    # Calculate CPU usage percentage (a basic calculation)
    cpu_usage=$(awk -v start="$cpu_stats_start" -v end="$cpu_stats_end" '
    BEGIN {
    split(start, a); split(end, b);
    total_start = a[2] + a[3] + a[4] + a[5] + a[6] + a[7] + a[8];
    total_end = b[2] + b[3] + b[4] + b[5] + b[6] + b[7] + b[8];
    idle_start = a[5]; idle_end = b[5];
    total_diff = total_end - total_start;
    idle_diff = idle_end - idle_start;
    usage = (total_diff - idle_diff) / total_diff * 100;
    print usage "%";
    }')
    
    output="${bold_blue}CPU Usage: $cpu_usage${reset_color}"
    echo -e "$output"
    log_command_output "$command" "$shell_command" "$output"
}

Show_Temp() {
    local command="Show Temperature"
    local shell_command="cat /sys/class/thermal/thermal_zone0/temp"
    
    echo "***********   Temperature Info   ***********"
    echo -e "${bold_blue}CPU Temperature:${reset_color}"
    
    temp_output=$(cat /sys/class/thermal/thermal_zone0/temp 2>/dev/null)
    if [ $? -eq 0 ]; then
        output="${bold_blue}Temperature: $temp_output${reset_color}"
    else
        output="${bold_blue}Temperature info not available${reset_color}"
    fi
    
    echo -e "$output"
    log_command_output "$command" "$shell_command" "$output"
}

Show_Frequency() {
    local command="Show Frequency"
    local shell_command="grep 'MHz' /proc/cpuinfo"
    
    echo "***********   CPU Frequency Info   ***********"
    
    frequency_output=$(grep "MHz" /proc/cpuinfo)
    output="${bold_blue}${frequency_output}${reset_color}"
    
    echo -e "$output"
    log_command_output "$command" "$shell_command" "$output"
}

Show_RAM_Memory() {
    local command="Show RAM Memory"
    local shell_command="grep MemTotal /proc/meminfo; grep MemAvailable /proc/meminfo"
    
    echo "***********   RAM Info   ***********"
    
    # Get total and available memory from /proc/meminfo
    total=$(grep MemTotal /proc/meminfo | awk '{print $2}')
    available=$(grep MemAvailable /proc/meminfo | awk '{print $2}')
    used=$((total - available))  # Calculates the used memory by subtracting available memory from total memory.
    
    # Convert to GB
    used_gb=$(echo "scale=2; $used / 1024 / 1024" | bc)
    total_gb=$(echo "scale=2; $total / 1024 / 1024" | bc)
    
    # Calculate usage percentage
    percentage=$(echo "scale=2; ($used / $total) * 100" | bc)
    
    output="${bold_blue}Used RAM: $used_gb GB${reset_color}\n${bold_blue}RAM Usage: $percentage%${reset_color}"
    
    echo -e "$output"
    log_command_output "$command" "$shell_command" "$output"
}

Show_FreeSpace() {
    local command="Show Disk Free Space"
    local shell_command="df -h --output=source,pcent,avail"
    
    echo "***********   Disk Info   ***********"
    
    free_space_output=$(df -h --output=source,pcent,avail)
    output="${bold_blue}${free_space_output}${reset_color}"
    
    echo -e "$output"
    log_command_output "$command" "$shell_command" "$output"
}


SystemInfo_MainLoop()
{
    while true; 
    do 
        echo ""
        echo ""
        echo ""
        echo  "******************* System *******************"
        echo "1. CPU Usage" 
        echo "2. Temperature" 
        echo "3. CPU Frequency" 
        echo "4. RAM Usage" 
        echo "5. Free space"
        echo "6. Exit"
        
        echo "Please Enter your choice"
        read UserInput    

        case $UserInput in 
        1) 
        Show_CPU_Usage
        ;;
        2) 
        Show_Temp
        ;;
        3) 
        Show_Frequency
        ;;
        4) 
        Show_RAM_Memory
        ;;    
        5) 
        Show_FreeSpace
        ;;    
        6) 
        echo "***********   Exit  ***********"
        break 
        ;;  
        esac

    done
}