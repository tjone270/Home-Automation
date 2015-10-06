--
--  AppDelegate.applescript
--  Room Controller
--
--  Created by Thomas Jones on 15/07/2014.
--  Copyright (c) 2014 TomTec Solutions. All rights reserved.
--

script AppDelegate
	property parent : class "NSObject"
	property relayControllerIP : "192.168.1.164"
	property relayControllerInternetDomain : "http://relaycontrol.tomtecsolutions.com/"
	property topLabel : missing value
	property title : ""
	-- IBOutlets
	property window : missing value
	property location : ""
	property cURL : ""
	
	on applicationWillFinishLaunching:aNotification
        set title to name of current application
		updateTopLabel("Attempting to establish a connection to the Relay Controller...")
		determineLocation()
		setLocation()
		updateTopLabel("System Ready to accept requests.")
	end applicationWillFinishLaunching:
	
	on applicationShouldTerminate:sender
		-- Insert code here to do any housekeeping before your application quits 
		return current application's NSTerminateNow
	end applicationShouldTerminate:
	
	on updateTopLabel(textReturned)
		tell topLabel to setStringValue:textReturned
	end updateTopLabel
	
	on relay1on:sender
		curlRequest("?relay11")
		updateTopLabel("Ceiling Lights in Thomas's Room are on.")
        delay 1
        updateTopLabel("System Ready to accept requests.")
	end relay1on:
	
	on relay1off:sender
		curlRequest("?relay10")
		updateTopLabel("Ceiling Lights in Thomas's Room are off.")
        delay 1
        updateTopLabel("System Ready to accept requests.")
	end relay1off:
	
	on relay2on:sender
		curlRequest("?relay21")
		updateTopLabel("Ceiling Fan in Thomas's Room is on.")
        delay 1
        updateTopLabel("System Ready to accept requests.")
	end relay2on:
	
	on relay2off:sender
		curlRequest("?relay20")
		updateTopLabel("Ceiling Fan in Thomas's Room is off.")
        delay 1
        updateTopLabel("System Ready to accept requests.")
	end relay2off:
	
	on relay3on:sender
		curlRequest("?relay41")
		updateTopLabel("Bedside Lamp power on Thomas's bedside table is on.")
        delay 1
        updateTopLabel("System Ready to accept requests.")
	end relay3on:
	
	on relay3off:sender
		curlRequest("?relay40")
		updateTopLabel("Bedside Lamp power on Thomas's bedside table is off.")
        delay 1
        updateTopLabel("System Ready to accept requests.")
	end relay3off:
	
	on allRelaysOn:sender
		curlRequest("?allON")
		updateTopLabel("All relays are on.")
        delay 1
        updateTopLabel("System Ready to accept requests.")
	end allRelaysOn:
	
	on allRelaysOff:sender
		curlRequest("?allOFF")
		updateTopLabel("All relays are off.")
        delay 1
        updateTopLabel("System Ready to accept requests.")
	end allRelaysOff:
    
    on resetSystem:sender
		curlRequest("?allOFF")
		updateTopLabel("System Reset")
        delay 1
        updateTopLabel("System Ready to accept requests.")
	end resetSystem
	
	on determineLocation()
		try
			updateTopLabel("Pinging intranet address of Relay Controller...")
			do shell script "ping -o -t 1 192.168.1.164"
			updateTopLabel("Response recieved from intranet address.")
			set location to "intranet"
		on error
			updateTopLabel("No response from intranet address. Trying internet address...")
			try
				do shell script "ping -o -t 1 tomtecsolutions.no-ip.biz"
				updateTopLabel("Response recieved from internet address.")
				set location to "internet"
			on error
				display alert title message "There was a problem connecting to the Relay Controller. Make sure you're connected to the internet, and try again. Try resetting the Relay Controller if problems persist." buttons {"Quit"} default button 1
				quit me
			end try
		end try
	end determineLocation
	
	on curlRequest(relayRequest)
		try
			do shell script "curl " & cURL & relayRequest
		on error errorString number errorNumber
			display alert title message "A error occurred whilst processing your request." & return & return & "Error Number: " & errorNumber & return & "Error String: " & errorString buttons {"Okay"} default button 1 as critical
		end try
	end curlRequest
	
	on setLocation()
		if location is "intranet" then
			set cURL to "http://192.168.1.164/"
		else if location is "internet" then
			set cURL to "http://relaycontrol.tomtecsolutions.com/"
		end if
	end setLocation
	
	on idle
		updateTopLabel("System Ready to accept requests.")
	end idle
	
end script