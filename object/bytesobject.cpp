object* bytes_new_frombytearr(char* arr, int len){
    object* obj=new_object(&BytesType);
    
    CAST_BYTES(obj)->val=arr;
    CAST_BYTES(obj)->len=len;
    return obj;
}

object* bytes_new_frombyte(char arr){
    object* obj=new_object(&BytesType);
    
    char* c=(char*)fpl_malloc(sizeof(char));
    c[0]=arr;
    CAST_BYTES(obj)->val=c;
    CAST_BYTES(obj)->len=1;
    return obj;
}

object* bytes_new(object* type, object* args, object* kwargs){
    int len=CAST_LIST(args)->size;
    if (CAST_DICT(kwargs)->val->size()!=0){
        vm_add_err(&ValueError, vm, "Expected no keyword arguments, got %d", CAST_DICT(kwargs)->val->size());
        return NULL;
    }
    if ((len!=1 && len!=0)){
        vm_add_err(&ValueError, vm, "Expected 1 or 0 arguments, got %d", len);
        return NULL;
    }

    if (len==0){
        return bytes_new_frombyte(0);
    }

    if (object_istype(list_index_int(args, 0)->type, &BytesType)){
        object* ret=list_index_int(args, 0);
        FPLINCREF(ret);
        return ret;
    }
    
    if (list_index_int(args, 0)->type->slot_iter!=NULL){
        object* o=list_index_int(args, 0);
        object* iter=o->type->slot_iter(o);
        
        if (iter==NULL){
            vm_add_err(&TypeError, vm, "Expected iterator, got '%s' object", iter->type->name->c_str());
            return NULL;
        }

        object* obj=new_object(CAST_TYPE(type));

        if (!object_istype(o->type, &StrType)){
            CAST_BYTES(obj)->val=(char*)fpl_malloc(sizeof(char)*128);
            
            o=iter->type->slot_next(iter);
            int i=0;
            int len=128;
            while (vm->exception==NULL){
                object* intob=object_int(o);
                if (intob==NULL || !object_istype(intob->type, &IntType)){
                    vm_add_err(&TypeError, vm, "'%s' object cannot be coerced to int", o->type->name->c_str());
                    return NULL; 
                }
                
                if (CAST_INT(intob)->val->to_int()>255 || CAST_INT(intob)->val->to_int()<0){
                    vm_add_err(&ValueError, vm, "Expected value in range(0, 256), got %d", CAST_INT(intob)->val->to_int());
                    return NULL;
                }
                CAST_BYTES(obj)->val[i++]=(char)(CAST_INT(intob)->val->to_int());
                FPLDECREF(intob);
                
                if (i==len){
                    i+=1;
                    len+=1;
                    CAST_BYTES(obj)->val=(char*)fpl_realloc((void*)CAST_BYTES(obj)->val, sizeof(char)*i);
                }
                
                o=iter->type->slot_next(iter);
            }
            if (vm->exception!=NULL){
                FPLDECREF(vm->exception);
                vm->exception=NULL;
            }
            FPLDECREF(iter);

            CAST_BYTES(obj)->len=i;
        }
        else{
            CAST_BYTES(obj)->val=(char*)fpl_malloc(CAST_STRING(o)->val->size());
            CAST_BYTES(obj)->len=CAST_STRING(o)->val->size();
            memcpy(CAST_BYTES(obj)->val, CAST_STRING(o)->val->c_str(), CAST_STRING(o)->val->size());
        }
        return obj;
    }

    vm_add_err(&TypeError, vm, "Expected iterator, got '%s' object", list_index_int(args, 0)->type->name->c_str());
    return NULL;
}

string _byte_repr(char c){
    char arr[50];
    sprintf(arr, "0x%x\0", (uint8_t)c);
    return string(arr, strlen(arr));
}

object* bytes_slice(object* self, object* idx){
    object* start=CAST_SLICE(idx)->start;
    object* end=CAST_SLICE(idx)->end;

    int start_v;
    int end_v;
    if (object_istype(start->type, &NoneType)){
        start_v=0;
    }
    else{
        start_v=CAST_INT(start)->val->to_int();
    }
    if (object_istype(end->type, &NoneType)){
        end_v=CAST_LIST(self)->size-1;
    }
    else{
        end_v=CAST_INT(end)->val->to_int();
    }
    
    if (start<0){
        start_v=0;
    }
    if (end_v>=CAST_BYTES(self)->len){
        end_v=CAST_BYTES(self)->len-1;
    }

    char* c=(char*)fpl_malloc(end_v-start_v);
    int index=0;
    for (int i=start_v; i<=end_v; i++){
        c[index++]=CAST_BYTES(self)->val[i];
    }
    return bytes_new_frombytearr(c, index);
}

object* bytes_get(object* self, object* idx){
    if (object_istype(idx->type, &SliceType)){
        return bytes_slice(self, idx);
    }     
    object* idx_=object_int(idx);
    if (idx_==NULL || !object_istype(idx->type, &IntType)){
        vm_add_err(&TypeError, vm, "'%s' object cannot be coerced to int",idx->type->name->c_str());
        FPLDECREF(idx_);
        return NULL;
    }
    if (*CAST_INT(idx_)->val>LONG_MAX || *CAST_INT(idx_)->val<LONG_MIN){
        vm_add_err(&IndexError, vm, "List index out of range");
        FPLDECREF(idx_);
        return NULL;
    }
    long lidx=CAST_INT(idx_)->val->to_long();
    if (lidx<0){
        lidx=lidx+CAST_BYTES(self)->len;
    }
    if (CAST_BYTES(self)->len<=lidx || lidx<0){
        vm_add_err(&IndexError, vm, "List index out of range");
        FPLDECREF(idx_);
        return NULL;
    }
    FPLDECREF(idx_);
    
    return bytes_new_frombyte(CAST_BYTES(self)->val[CAST_INT(idx)->val->to_long_long()]);
}

object* bytes_len(object* self){
    return new_int_fromint(CAST_BYTES(self)->len);
}

object* bytes_repr(object* self){
    string s="";
    for (int i=0; i<CAST_BYTES(self)->len; i++){
        s+=string(1, CAST_BYTES(self)->val[i]);
    }
    return str_new_fromstr(s);
}


object* bytes_str(object* self){
    string s="b'";
    for (int i=0; i<CAST_BYTES(self)->len; i++){
        s+=_byte_repr(CAST_BYTES(self)->val[i]);
        if (i==128){
            s+="... ";
            break;
        }
        if (i!=CAST_BYTES(self)->len-1){
            s+=", ";
        }
    }
    s+="'";
    return str_new_fromstr(s);
}

object* bytes_bool(object* self){
    return new_bool_true();
}

object* bytes_cmp(object* self, object* other, uint8_t type){
    if (type==CMP_IN){
        return object_in_iter(other, self);
    }
    if (self->type!=other->type){
        return NULL;
    }
    if (type==CMP_EQ){
        if (CAST_BYTES(self)->len!=CAST_BYTES(other)->len){
            return new_bool_false();
        }
        if (memcmp(CAST_BYTES(self)->val, CAST_BYTES(other)->val, CAST_BYTES(self)->len)==0){
            return new_bool_true();
        }
        return new_bool_false();
    }
    if (type==CMP_NE){
        if (CAST_BYTES(self)->len==CAST_BYTES(other)->len){
            return new_bool_false();
        }
        if (!memcmp(CAST_BYTES(self)->val, CAST_BYTES(other)->val, CAST_BYTES(self)->len)==0){
            return new_bool_true();
        }
        return new_bool_false();
    }
    return NULL;
}

void bytes_del(object* obj){
    fpl_free((void*)CAST_BYTES(obj)->val);
}

object* bytes_iter(object* self){
    //Make an iterator
    object* iter=new_object(&BytesIterType);
    CAST_BYTESITER(iter)->val=(char*)fpl_malloc(CAST_BYTES(self)->len);
    CAST_BYTESITER(iter)->len=CAST_BYTES(self)->len;
    CAST_BYTESITER(iter)->idx=0;
    memcpy(CAST_BYTESITER(iter)->val, CAST_BYTES(self)->val, CAST_BYTESITER(iter)->len);
    return iter;
}

void bytes_iter_del(object* self){
    fpl_free((void*)CAST_BYTESITER(self)->val);
}

object* bytes_iter_next(object* self){
    if (CAST_BYTESITER(self)->idx+1>CAST_BYTESITER(self)->len){
        vm_add_err(&StopIteration, vm, "Iterator out of data");
        return NULL;
    }
    return new_int_fromint((int)CAST_BYTESITER(self)->val[CAST_BYTESITER(self)->idx++]);
}

object* bytes_iter_cmp(object* self, object* other, uint8_t type){
    if (self->type!=other->type){
        return NULL;
    }
    if (type==CMP_EQ){
        if (CAST_BYTESITER(self)->len!=CAST_BYTESITER(other)->len){
            return new_bool_false();
        }
        if (memcmp(CAST_BYTESITER(self)->val, CAST_BYTESITER(other)->val, CAST_BYTESITER(self)->len)==0){
            return new_bool_true();
        }
        return new_bool_false();
    }
    if (type==CMP_NE){
        if (CAST_BYTESITER(self)->len==CAST_BYTESITER(other)->len){
            return new_bool_false();
        }
        if (!memcmp(CAST_BYTESITER(self)->val, CAST_BYTESITER(other)->val, CAST_BYTESITER(self)->len)==0){
            return new_bool_true();
        }
        return new_bool_false();
    }
    return NULL;
}

object* bytes_iter_bool(object* self){
    return new_bool_true();
}

object* bytes_add(object* self, object* other){
    if (other->type!=&BytesType){
        vm_add_err(&TypeError, vm, "Invalid operand types for +: '%s', and '%s'.", self->type->name->c_str(), other->type->name->c_str());
        return NULL;
    }

    char* c=(char*)fpl_malloc(CAST_BYTES(self)->len+CAST_BYTES(other)->len);
    memcpy(c, CAST_BYTES(self)->val, CAST_BYTES(self)->len);
    memcpy(c+CAST_BYTES(self)->len, CAST_BYTES(other)->val, CAST_BYTES(other)->len);

    object* obj=new_object(&BytesType);
    
    CAST_BYTES(obj)->val=c;
    CAST_BYTES(obj)->len=CAST_BYTES(self)->len+CAST_BYTES(other)->len;
    
    return obj;
}

object* bytes_mul(object* self, object* other){
    if (other->type!=&IntType){
        vm_add_err(&TypeError, vm, "Invalid operand types for *: '%s', and '%s'.", self->type->name->c_str(), other->type->name->c_str());
        return NULL;
    }

    int len_=CAST_BYTES(self)->len;
    int len=CAST_INT(other)->val->to_int();
        
    char* c=(char*)fpl_malloc(len_*len);
    
    for (int i=0; i<len; i++){
        memcpy(c, (CAST_BYTES(self)->val)+(i*len_), len_);
    }

    object* obj=new_object(&BytesType);
    
    CAST_BYTES(obj)->val=c;
    CAST_BYTES(obj)->len=len;
    return obj;
}

object* bytes_decode_meth(object* selftp, object* args, object* kwargs){
    long len= CAST_LIST(args)->size;
    if (CAST_DICT(kwargs)->val->size()!=0){
        vm_add_err(&ValueError, vm, "Expected no keyword arguments, got %d", CAST_DICT(kwargs)->val->size());
        return NULL;
    }
    if (len!=2){
        vm_add_err(&ValueError, vm, "Expected 2 arguments, got %d", len);
        return NULL; 
    }
    object* self=tuple_index_int(args, 0);  
    object* encoding=tuple_index_int(args, 1);   
    

    if (!object_istype(encoding->type, &StrType)){
        vm_add_err(&ValueError, vm, "Expected str, got '%s'", encoding->type->name->c_str());
        return NULL; 
    }  

    string enc=*CAST_STRING(encoding)->val;
    
    iconv_t cd = iconv_open("UTF-8", enc.c_str());
    if((int) cd == -1) {
        if (errno == EINVAL) {
            vm_add_err(&ValueError, vm, "Invalid conversion");
            return NULL; 
        }
    }

    size_t s_size=CAST_BYTES(self)->len;
    size_t new_size=s_size;
    size_t _new_size=new_size;

    const char* orig_str=CAST_BYTES(self)->val;
    char* converted=(char*)fpl_calloc(new_size, sizeof(char));
    char* start=converted;
    
    int ret = iconv(cd, &orig_str, &s_size, &converted, &new_size);
    
    if((iconv_t)ret == (iconv_t)(-1)) {
        vm_add_err(&ValueError, vm, "Invalid multibyte sequence encountered");
        return NULL; 
    }
    iconv_close(cd);

    string s(start);

    fpl_free(start);

    return str_new_fromstr(s);
}