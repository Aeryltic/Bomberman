timePassed = 0
nextPrintAt = 1000

protected = {
	protected_var = 1
}

function pass(item)
	return item
end

function updateTime()
	display.text = os.date("%H:%M:%S")
end

function printsin(angle)
	print(math.sin(angle*math.pi/180))
  return "clean execution"
end

function safelyExecute(command)
	-- docelowo ma sprawdzać czy można wykonać, chociaż o to powinniśmy zadbać już na poziomie C++
	-- żeby nie tworzyć nowych zmiennych i nie używać ich do niecnych celów
	-- i zablokować dostęp do pewnych, które zmieniane być nie powinny
	-- jakiś namespace jak np. "locked", "protected", "hidden", "private"
	loadstring(command)
  return "clean execution"
end
