void gil_lock(int id){
    _gil.lock();
    ::vm=interpreter.vm_map->at(id);
}

int gil_unlock(){
    uint32_t id=vm->id;
    _gil.unlock();
    return id;
}