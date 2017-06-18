current_path = string.gsub(debug.getinfo(1).short_src, "^(.+\\)[^\\]+$", "%1")
print("current path is " .. current_path)

dofile("data/scripts/config.lua")
dofile("data/scripts/script.lua")
dofile("data/scripts/entities.lua")
dofile("data/scripts/action_handlers.lua")
dofile("data/scripts/precondition_scanners.lua")

function initSettings()

end

function reload()

end

function init_game(entity_manager)
    entity_manager:make_object("water_source", 500, 100);
    entity_manager:make_object("tree", 500, 500);
    entity_manager:make_object("tree", 800, 500);

    entity_manager:make_object("store", 300, 300);
    entity_manager:make_object("store", 700, 300);

    entity_manager:make_object("inn", 600, 600);

    entity_manager:make_object("monster", 10, 10);
    
    x = 3
    y = 3
    
    for i=1, y, 1 do
        for j=1, x, 1 do
            entity_manager:make_object("ant", j*200, i*200);
        end
    end
end