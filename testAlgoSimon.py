listInput = [1, 1, 1, 2, 1, 4, 3, 3, 4]
buzzerSound = ""
ledId = ""

def buzzer(a):
    if (a == 1):
        """buzzerSound = "Do"""
        print("Do")
    elif (a == 2):
        """buzzerSound = "Ré"""
        print("Ré")
    elif (a == 3):
        """buzzerSound = "Mi"""
        print("Mi")
    elif (a == 4):
        """buzzerSound = "Fa"""
        print("Fa")
    """playBuzzer(buzzerSound)"""

def led(a):
    if (a == 1):
        """ledId = "Red"""
        print("Red")
    elif (a == 2):
        """ledId = "Yellow"""
        print("Yellow")
    elif (a == 3):
        """ledId = "Green"""
        print("Green")
    elif (a == 4):
        """ledId = "Blue"""
        print("Blue")
    """turnLedOn(ledId)"""

def recursive(tab):
    input = tab.pop(0)
    if (len(tab) <= 0):
        buzzer(input)
        led(input)
        return
    buzzer(input)
    led(input)
    return recursive(tab)

recursive(listInput)