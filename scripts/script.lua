timePassed = 0
nextPrintAt = 1000

function pass(item)
	return item
end

function passDisplay(_display)
	display = _display
	print("display passed")
end

function updateTime(msPassed)
	timePassed = timePassed + msPassed
	if timePassed >= nextPrintAt then
		--display.text = "passed: " .. timePassed
		nextPrintAt = nextPrintAt + 1000
	end
end

function printsin(angle)
	print(math.sin(angle*math.pi/180))
end