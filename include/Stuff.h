entity_ptr EntityManager::getWorld()
{
    if(!_world.lock())
    {
        for(auto w_m : _entity)
        {
            entity_ptr w = w_m.second;
            if(w->has<World>())
            {
                _world = w;
                break;
            }
        }
    }
    return _world.lock();
}

entity_ptr EntityManager::getPlayer()
{
    if(!_player.lock())
    {
        for(auto p_m : _entity)
        {
            entity_ptr p = p_m.second;
            if(p->has<KeyboardController>())
            {
                _player = p;
                break;
            }
        }
    }
    return _player.lock();
}
