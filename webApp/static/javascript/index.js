var jsn = {
    'led1' : 'OFF',
    'led2' : 'OFF',
    'fan' : 'OFF',
    'plug' : 'OFF'
}

console.log("Javascript Working...");

/* SOME FALTU GREET MESSAGE!!!
// Send connection message to flask using POST method
fetch('/control', {
    // Declare what type of data we're sending
    headers: {
    'Content-Type': 'application/json'
    },
    // Specify the method
    method: 'POST',
    // A JSON payload
    body: JSON.stringify({
        "greet": "[status] Web connection successful."
    })
    }).then(function (response) { 
        // At this point, Flask has printed our JSON
        return response.text();
        }).then(function (text) {

            console.log('Message Sent. ');
            console.log('response: ');
            // Should be 'OK' if everything was successful
            console.log(text);
    });
    */

// Function to toggle the color of led when called.
/*function toggle_state(id)
{
        if (id == 'led1'){
            if (jsn.led1 == 'ON')
                jsn.led1 = 'OFF'
            else
                jsn.led1 = 'ON'
        }
        else if (id == 'led2'){
            if (jsn.led2 == 'ON')
                jsn.led2 = 'OFF'
            else
                jsn.led2 = 'ON'
        }
        else if (id == 'fan'){
            if (jsn.fan == 'ON')
                jsn.fan = 'OFF'
            else
                jsn.fan = 'ON'
        }
        else if (id == 'plug'){
            if (jsn.plug == 'ON')
                jsn.plug = 'OFF'
            else
                jsn.plug = 'ON'
        }
        // Send message to server using POST method
        fetch('/control', {
            // Declare what type of data we're sending
            headers: {
            'Content-Type': 'application/json'
            },
            // Specify the method
            method: 'POST',
            // A JSON payload
            body: JSON.stringify(jsn)
            }).then(function (response) { 
                // At this point, Flask has printed our JSON
                return response.text();
                }).then(function (text) {
        
                    console.log('Message Sent. ');
                    console.log('response: ');
                    // Should be 'OK' if everything was successful
                    console.log(text);
        });
}*/

/*function update_switch(j)
{
    if (j.led1 != jsn.led1){
        toggle_state('led1');
        jsn.led1 = j.led1;

    }
    
    if (j.led2 != jsn.led2){
        toggle_state('led2');
        jsn.led2 = j.led2;
    }

    if (j.fan != jsn.fan){
        toggle_state('fan');
        jsn.fan = j.fan;
    }

    if (j.plug != jsn.plug){
        toggle_state('plug');
        jsn.plug = j.plug;
    }
}*/


/*var intervalId = window.setInterval(function(){
    // Send the request using GET methood (default).
    fetch('/control')
        .then(function (response) {
            return response.json(); // But parse it as JSON this time
        })
        .then(function (json) {
            console.log('GET response as JSON:');
            console.log(json); // Here’s our JSON object

            //update_switch(json)
        })
    }, 5000);*/
    myFunction();
    function myFunction() {
        setInterval(function(){
        jsn.led1 = "{{ led1 }}";
        console.log(json.led1);
        document.getElementById('led1').style.color = "rgb(221, 221, 0)";
        
    }, 2000);
    }