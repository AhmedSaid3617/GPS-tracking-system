<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
</head>
<body>
    <h1>Project Description</h1>
    <p>The goal of this project is to develop an embedded system using C programming that gathers real-time positional coordinates while a microcontroller is in motion (GPS tracking system using TM4C123G LaunchPad) after power-on until a destination point is reached. The collected data will then be efficiently transferred to a personal computer (PC) and visualized on a map application.</p>
    
    <p>There are three possible options for the definition of the destination point:</p>
    <ol>
        <li>Once the moved distance exceeds 100m, stop adding new points to the trajectory and the last point added to the trajectory is the target destination.</li>
        <li>Stop adding new points when a push button is pressed, and the last point added to the trajectory is the last destination.</li>
        <li>Predefine the destination point in your code and when the system reaches this point, stop adding new points to the trajectory.</li>
    </ol>
    
    <p>Other functions required by the system:</p>
    <ol>
        <li>When the destination point is reached the built-in LED of the launchpad should be turned on.</li>
        <li>The system should check for UART commands from the PC and if the PC sends the command ‘U’ then the system should send the stored trajectory to the PC.</li>
    </ol>
</body>
</html>
