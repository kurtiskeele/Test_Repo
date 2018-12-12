FILE=/sys/class/gpio/gpio13
if [ -e "$FILE" ]; then
	echo "gpio13 exitsts!\n"
else
	echo "gpio13 does not exit, creating it..."
	
	# setup GPIO 13 as an output
	echo "13" > /sys/class/gpio/export
	echo "out" > /sys/class/gpio/gpio13/direction
	echo "[DONE]\n"

fi

# ensure pin starts as high (3.3v)
echo "Pin set to high...\n"
echo "1" > /sys/class/gpio/gpio13/value
sleep 1

# toggle pin low (gnd)
echo "Pin set to low...\n"
echo "0" > /sys/class/gpio/gpio13/value
sleep 1

# finish with pin high (3.3v)
echo "Pin set to high...\n"
echo "1" > /sys/class/gpio/gpio13/value

echo "Reset sequence complete\n"
