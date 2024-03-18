## READ ME

*Purpose:* This code is designed to control an LED light based on instructions received from a server and send temperature readings back to the server because master phill

*Functionality:*

*setup() function:*
    * Initializes serial communication for debugging.
    * Initializes the DallasTemperature library for temperature sensor communication.
    * Connects to the WiFi network specified in `env.h` (SSID and password).
    * Prints the assigned IP address upon successful connection.

* *loop() function:*
    * Checks WiFi connection status. If connected:
        * Fetches the light status (`light`) from the server using a GET request with an API key for authentication (defined in `env.h`).
        * Controls the LED connected to `led_pin` based on the received light status (true: ON, false: OFF).
        * Prints the received light status to the serial monitor.
        * Requests temperature readings from the sensor.
        * Calls the `putTemp` function to send the temperature reading to the server using a PUT request with an API key.
        * Prints the temperature reading to the serial monitor.
    * If WiFi is disconnected, prints a message to the serial monitor.

* *putTemp(float temp)* function:
    * Takes a float value representing the temperature as input.
    * Creates a JSON document with a key `"temp"` and assigns the input temperature value.
    * Sends the JSON document to the server specified by `tempendpoint` using a PUT request with an API key for authentication.
    * Prints success or error messages based on the HTTP response code.


