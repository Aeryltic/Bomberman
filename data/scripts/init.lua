base_dir = "data/scripts"
files_done = {} -- przechowuje dane o plikach, które zostały wykonane

function initSettings()

end

function string.ends(String, End)
   return End=='' or string.sub(String,-string.len(End))==End
end

function print_table(table)
  logs.open('printing table:')
  for k, v in pairs(table) do
      logs.log('\"'..tostring(k)..'\": ('..tostring(v)..')')
  end
  logs.close('done.')
end

function scandir(directory)
    local i, t, popen = 0, {}, io.popen
    local pfile = popen('dir "'..directory..'" /b') -- Windows only
    for filename in pfile:lines() do
        i = i + 1
        t[i] = filename
    end
    pfile:close()
    return t
end

function dofile_safe(filename)
  if files_done[filename] == nil then
    dofile(filename)
    files_done[filename] = true
    logs.log('safely executed: '..filename)
  end
end

function do_all_files(dirname)
  if not string.ends(dirname, "not_used") then -- tego tu być nie winno
    local files = scandir(dirname)
    
    for k, file in pairs(files) do
      full_path = dirname.."/"..file
      
      if string.ends(file, ".lua") then
        dofile_safe(full_path)
      else -- pozostałe pliki traktuje jako katalogi, 
        do_all_files(full_path)
      end
      
    end
  end
end

function init_lua_side()
  logs.open("initializing lua's side...")
  files_done = {}
  
  current_path = string.gsub(debug.getinfo(1).short_src, "^(.+\\)[^\\]+$", "%1")
  files_done[current_path] = true
  do_all_files(base_dir)
  logs.close("done.")
end

function reload(filepath)
  logs.open("reloading...")
  if filepath == nil then -- jeśli nie podano ścieżki odświeżamy wszystko
    files_done = {}
    
    current_path = string.gsub(debug.getinfo(1).short_src, "^(.+\\)[^\\]+$", "%1")
    files_done[current_path] = true
    do_all_files(base_dir)
  else
    files_done[filepath] = nil
    dofile_safe(filepath)
  end
  --print_table(_G)
  logs.log("refreshing references")
  Engine.script_sys():refresh_refs() -- funkcja z poziomu C++
  losg.close("done.")
end

--[[..................................MAIN..........................................]]--
--[[
--if ___main___ == nil then -- to zapewnia jedynie, że tylko raz wykonamy tą część
if debug.getinfo(2) == nil then -- if "main" then
  --__main__ = true
  reload()
end
]]--