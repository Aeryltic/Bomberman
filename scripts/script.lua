timePassed = 0
nextPrintAt = 1000

updateTime = function(displayManager, msPassed)
	timePassed = timePassed + msPassed
	if timePassed >= nextPrintAt then
		displayManager:showDialog(tostring(timePassed))
		nextPrintAt = nextPrintAt + 1000
	end
end
