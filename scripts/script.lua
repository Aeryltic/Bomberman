timePassed = 0
nextPrintAt = 1000

protected = {
	protected_var = 1
}

function pass(item)
	return item
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

function safelyExecute(command)
	-- docelowo ma sprawdzać czy można wykonać, chociaż o to powinniśmy zadbać już na poziomie C++
	-- żeby nie tworzyć nowych zmiennych i nie używać ich do niecnych celów
	-- i zablokować dostęp do pewnych, które zmienanie być nie powinny
	-- jakiś namespace jak np. "locked", "protected", "hidden", "private"
	loadstring(command)
end