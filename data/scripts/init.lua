current_path = string.gsub(debug.getinfo(1).short_src, "^(.+\\)[^\\]+$", "%1")
print("current path is " .. current_path)

--dofile("data/scripts/config.lua")
dofile("data/scripts/script.lua")
--dofile("data/scripts/entities.lua")
dofile("data/scripts/AI/action_handlers.lua")
dofile("data/scripts/AI/precondition_scanners.lua")

function initSettings()

end

function reload()

end

function init_game(entity_manager)
    entity_manager:make_object("water_source", 500, 100);
    entity_manager:make_object("bush", 500, 500);
    entity_manager:make_object("bush", 700, 500);

    entity_manager:make_object("store", 300, 300);
    entity_manager:make_object("store", 700, 300);

    entity_manager:make_object("inn", 600, 600);

    entity_manager:make_object("monster", 10, 10);
    
    x = 3
    y = 3
    
    sx = 350
    sy = 350   
    
    for i=1, y, 1 do
        for j=1, x, 1 do
            entity_manager:make_object("food_picker", sx + j*50, sy + i*50);
        end
    end
    
    x = 2
    y = 2
    
    sx = 550
    sy = 350
    
    for i=1, y, 1 do
        for j=1, x, 1 do
            entity_manager:make_object("wood_picker", sx + j*50, sy + i*50);
        end
    end
    
    x = 5
    y = 3
    
    sx = 550
    sy = 750
    
    for i=1, y, 1 do
        for j=1, x, 1 do
            entity_manager:make_object("tree", sx + j*50, sy + i*30);
        end
    end
end