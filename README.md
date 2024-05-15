<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
</head>
<body>
    <h1>Project Description</h1>
    <p>The goal of this project is to develop an embedded system using C programming that gathers real-time positional coordinates while a microcontroller is in motion (GPS tracking system using TM4C123G LaunchPad) after power-on until a destination point is reached. The collected data will then be efficiently transferred to a personal computer (PC) and visualized on a map application.</p>
    
    <p>Other functions required by the system:</p>
    <ol>
        <li>When the destination point is reached the built-in LED of the launchpad should be turned on.</li>
        <li>The system should check for UART commands from the PC and if the PC sends the command ‘U’ then the system should send the stored trajectory to the PC.</li>
    </ol>


    <p>EEPROM</p>
    <ol>
        <li>The default for any program is that the run time data is saved in the RAM, which is a volatile memory, so as the we cut the power from the kit data is lost.</li>
        <li>Sometimes there are critical data that shouldn't be lost even if the power is off, so we need a type of Non volatile memory to hold this important data.</li>
        <li>
        EEPROM (Electrically Erasable Programmable Read-Only Memory) is crucial in Arm processors for non-volatile storage. It retains data even when power is off, making it ideal for storing configuration settings, calibration data, and user preferences. Additionally, its execute-while-write capability allows real-time updates without interrupting system operation
        </li>

        <li> We used the EEPROM of the TivaC kit we have by writing a driver from scratch to be able to fully control the EEPROM and save the Coordinates we parse from the GPS module in the EEPROM inorder to prevent this data from loss if the power was turned off from the kit</li>
    </ol>


         <h3>Functions of the driver and there usage:</h3>

         <table>
            <tr>
                <th>Function</th>
                <th>Usage</th>
            </tr>

            <tr>
                <td>unsigned long EEPROM_Read(int address)</td>
                <td>Read data of a certain address of the EEPROM</td>
            </tr>

            <tr>
                <td>void EEPROM_Write(unsigned int address, unsigned long value)</td>
                <td>Saves a certain value in a certain adress of the EEPROM</td>
            </tr>

            <tr>
                <td>EEPROM_Init_Status EEPROM_Init()</td>
                <td>------------</td>
            </tr>

             <tr>
                <td>EEPROM_write_array(float coordinates[][2],unsigned long number_of_saved_reading)</td>
                <td>Saves the array of coordinates the module gets in contiguous locations starting by the number of saved Coordinates  </td>
            </tr>

            <tr>
                <td>unsigned long EEPROM_read_coordniates()</td>
                <td>Reads the saved array of coordinates saved in the EEPROM</td>
            </tr>
</body>
</html>
