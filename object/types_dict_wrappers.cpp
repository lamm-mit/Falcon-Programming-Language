object* type_wrapper_add(object* self, object* args, object* kwargs){
    if (CAST_DICT(kwargs)->val->size()!=0){
        vm_add_err(&ValueError, vm, "Expected no keyword arguments, got %d", CAST_DICT(kwargs)->val->size());
        return NULL;
    }
    if (CAST_LIST(args)->size!=2){
        vm_add_err(&ValueError, vm, "Expected 2 arguments, got %d",CAST_LIST(args)->size);
        return NULL;
    }
    object* ret=CAST_TYPE(self)->slot_number->slot_add(list_index_int(args, 0), list_index_int(args, 1));
    if (ret==NULL){
        vm_add_err(&TypeError, vm, "Invalid operand types for +: '%s', and '%s'.", self->type->name->c_str(), list_index_int(args, 1)->type->name->c_str());
        return NULL;
    }
    return ret;
}

object* type_wrapper_sub(object* self, object* args, object* kwargs){
    if (CAST_DICT(kwargs)->val->size()!=0){
        vm_add_err(&ValueError, vm, "Expected no keyword arguments, got %d", CAST_DICT(kwargs)->val->size());
        return NULL;
    }
    if (CAST_LIST(args)->size!=2){
        vm_add_err(&ValueError, vm, "Expected 2 arguments, got %d",CAST_LIST(args)->size);
        return NULL;
    }

    object* ret=CAST_TYPE(self)->slot_number->slot_sub(list_index_int(args, 0), list_index_int(args, 1));
    if (ret==NULL){
        vm_add_err(&TypeError, vm, "Invalid operand types for -: '%s', and '%s'.", self->type->name->c_str(), list_index_int(args, 1)->type->name->c_str());
        return NULL;
    }
    return ret;
}

object* type_wrapper_mul(object* self, object* args, object* kwargs){
    if (CAST_DICT(kwargs)->val->size()!=0){
        vm_add_err(&ValueError, vm, "Expected no keyword arguments, got %d", CAST_DICT(kwargs)->val->size());
        return NULL;
    }
    if (CAST_LIST(args)->size!=2){
        vm_add_err(&ValueError, vm, "Expected 2 arguments, got %d",CAST_LIST(args)->size);
        return NULL;
    }
    
    object* ret=CAST_TYPE(self)->slot_number->slot_mul(list_index_int(args, 0), list_index_int(args, 1));
    if (ret==NULL){
        vm_add_err(&TypeError, vm, "Invalid operand types for *: '%s', and '%s'.", self->type->name->c_str(), list_index_int(args, 1)->type->name->c_str());
        return NULL;
    }
    return ret;
}

object* type_wrapper_div(object* self, object* args, object* kwargs){
    if (CAST_DICT(kwargs)->val->size()!=0){
        vm_add_err(&ValueError, vm, "Expected no keyword arguments, got %d", CAST_DICT(kwargs)->val->size());
        return NULL;
    }
    if (CAST_LIST(args)->size!=2){
        vm_add_err(&ValueError, vm, "Expected 2 arguments, got %d",CAST_LIST(args)->size);
        return NULL;
    }

    object* ret=CAST_TYPE(self)->slot_number->slot_div(list_index_int(args, 0), list_index_int(args, 1));
    if (ret==NULL){
        vm_add_err(&TypeError, vm, "Invalid operand types for /: '%s', and '%s'.", self->type->name->c_str(), list_index_int(args, 1)->type->name->c_str());
        return NULL;
    }
    return ret;
}

object* type_wrapper_bool(object* self, object* args, object* kwargs){
    if (CAST_DICT(kwargs)->val->size()!=0){
        vm_add_err(&ValueError, vm, "Expected no keyword arguments, got %d", CAST_DICT(kwargs)->val->size());
        return NULL;
    }
    if (CAST_LIST(args)->size!=1){
        vm_add_err(&ValueError, vm, "Expected 1 argument, got %d",CAST_LIST(args)->size);
        return NULL;
    }
    
    object* ret=CAST_TYPE(self)->slot_number->slot_bool(list_index_int(args, 0));
    if (ret==NULL){
        vm_add_err(&TypeError, vm, "'%s' object cannot be coerced to bool", self->type->name->c_str());
        return NULL;
    }
    return ret;
}

object* type_wrapper_neg(object* self, object* args, object* kwargs){
    if (CAST_DICT(kwargs)->val->size()!=0){
        vm_add_err(&ValueError, vm, "Expected no keyword arguments, got %d", CAST_DICT(kwargs)->val->size());
        return NULL;
    }
    if (CAST_LIST(args)->size!=1){
        vm_add_err(&ValueError, vm, "Expected 1 argument, got %d",CAST_LIST(args)->size);
        return NULL;
    }
    
    object* ret=CAST_TYPE(self)->slot_number->slot_neg(list_index_int(args, 0));
    if (ret==NULL){
        vm_add_err(&TypeError, vm, "Invalid unary operand -: '%s'.", self->type->name->c_str());
        return NULL;
    }
    return ret;
}

object* type_wrapper_int(object* self, object* args, object* kwargs){
    if (CAST_DICT(kwargs)->val->size()!=0){
        vm_add_err(&ValueError, vm, "Expected no keyword arguments, got %d", CAST_DICT(kwargs)->val->size());
        return NULL;
    }
    if (CAST_LIST(args)->size!=1){
        vm_add_err(&ValueError, vm, "Expected 1 argument, got %d",CAST_LIST(args)->size);
        return NULL;
    }
    
    object* ret=CAST_TYPE(self)->slot_number->slot_int(list_index_int(args, 0));
    if (ret==NULL){
        vm_add_err(&TypeError, vm, "'%s' object cannot be coerced to int", self->type->name->c_str());
        return NULL;
    }
    return ret;
}

object* type_wrapper_float(object* self, object* args, object* kwargs){
    if (CAST_DICT(kwargs)->val->size()!=0){
        vm_add_err(&ValueError, vm, "Expected no keyword arguments, got %d", CAST_DICT(kwargs)->val->size());
        return NULL;
    }
    if (CAST_LIST(args)->size!=1){
        vm_add_err(&ValueError, vm, "Expected 1 argument, got %d",CAST_LIST(args)->size);
        return NULL;
    }
    
    object* ret=CAST_TYPE(self)->slot_number->slot_float(list_index_int(args, 0));
    if (ret==NULL){
        vm_add_err(&TypeError, vm, "'%s' object cannot be coerced to float", self->type->name->c_str());
        return NULL;
    }
    return ret;
}

object* type_wrapper_pow(object* self, object* args, object* kwargs){
    if (CAST_DICT(kwargs)->val->size()!=0){
        vm_add_err(&ValueError, vm, "Expected no keyword arguments, got %d", CAST_DICT(kwargs)->val->size());
        return NULL;
    }
    if (CAST_LIST(args)->size!=2){
        vm_add_err(&ValueError, vm, "Expected 2 arguments, got %d",CAST_LIST(args)->size);
        return NULL;
    }
    
    object* ret=CAST_TYPE(self)->slot_number->slot_pow(list_index_int(args, 0), list_index_int(args, 1));
    if (ret==NULL){
        vm_add_err(&TypeError, vm, "Invalid operand types for **: '%s', and '%s'.", self->type->name->c_str(), list_index_int(args, 1)->type->name->c_str());
        return NULL;
    }
    return ret;
}

object* type_wrapper_mod(object* self, object* args, object* kwargs){
    if (CAST_DICT(kwargs)->val->size()!=0){
        vm_add_err(&ValueError, vm, "Expected no keyword arguments, got %d", CAST_DICT(kwargs)->val->size());
        return NULL;
    }
    if (CAST_LIST(args)->size!=2){
        vm_add_err(&ValueError, vm, "Expected 2 arguments, got %d",CAST_LIST(args)->size);
        return NULL;
    }
    
    object* ret=CAST_TYPE(self)->slot_number->slot_mod(list_index_int(args, 0), list_index_int(args, 1));
    if (ret==NULL){
        vm_add_err(&TypeError, vm, "Invalid operand types for %: '%s', and '%s'.", self->type->name->c_str(), list_index_int(args, 1)->type->name->c_str());
        return NULL;
    }
    return ret;
}

object* type_wrapper_and(object* self, object* args, object* kwargs){
    if (CAST_DICT(kwargs)->val->size()!=0){
        vm_add_err(&ValueError, vm, "Expected no keyword arguments, got %d", CAST_DICT(kwargs)->val->size());
        return NULL;
    }
    if (CAST_LIST(args)->size!=2){
        vm_add_err(&ValueError, vm, "Expected 2 arguments, got %d",CAST_LIST(args)->size);
        return NULL;
    }
    
    object* ret=CAST_TYPE(self)->slot_number->slot_and(list_index_int(args, 0), list_index_int(args, 1));
    if (ret==NULL){
        vm_add_err(&TypeError, vm, "Invalid operand types for &: '%s', and '%s'.", self->type->name->c_str(), list_index_int(args, 1)->type->name->c_str());
        return NULL;
    }
    return ret;
}

object* type_wrapper_or(object* self, object* args, object* kwargs){
    if (CAST_DICT(kwargs)->val->size()!=0){
        vm_add_err(&ValueError, vm, "Expected no keyword arguments, got %d", CAST_DICT(kwargs)->val->size());
        return NULL;
    }
    if (CAST_LIST(args)->size!=2){
        vm_add_err(&ValueError, vm, "Expected 2 arguments, got %d",CAST_LIST(args)->size);
        return NULL;
    }
    
    object* ret=CAST_TYPE(self)->slot_number->slot_or(list_index_int(args, 0), list_index_int(args, 1));
    if (ret==NULL){
        vm_add_err(&TypeError, vm, "Invalid operand types for |: '%s', and '%s'.", self->type->name->c_str(), list_index_int(args, 1)->type->name->c_str());
        return NULL;
    }
    return ret;
}

object* type_wrapper_xor(object* self, object* args, object* kwargs){
    if (CAST_DICT(kwargs)->val->size()!=0){
        vm_add_err(&ValueError, vm, "Expected no keyword arguments, got %d", CAST_DICT(kwargs)->val->size());
        return NULL;
    }
    if (CAST_LIST(args)->size!=2){
        vm_add_err(&ValueError, vm, "Expected 2 arguments, got %d",CAST_LIST(args)->size);
        return NULL;
    }
    
    object* ret=CAST_TYPE(self)->slot_number->slot_xor(list_index_int(args, 0), list_index_int(args, 1));
    if (ret==NULL){
        vm_add_err(&TypeError, vm, "Invalid operand types for ^: '%s', and '%s'.", self->type->name->c_str(), list_index_int(args, 1)->type->name->c_str());
        return NULL;
    }
    return ret;
}

object* type_wrapper_lshift(object* self, object* args, object* kwargs){
    if (CAST_DICT(kwargs)->val->size()!=0){
        vm_add_err(&ValueError, vm, "Expected no keyword arguments, got %d", CAST_DICT(kwargs)->val->size());
        return NULL;
    }
    if (CAST_LIST(args)->size!=2){
        vm_add_err(&ValueError, vm, "Expected 2 arguments, got %d",CAST_LIST(args)->size);
        return NULL;
    }
    
    object* ret=CAST_TYPE(self)->slot_number->slot_lshift(list_index_int(args, 0), list_index_int(args, 1));
    if (ret==NULL){
        vm_add_err(&TypeError, vm, "Invalid operand types for <<: '%s', and '%s'.", self->type->name->c_str(), list_index_int(args, 1)->type->name->c_str());
        return NULL;
    }
    return ret;
}

object* type_wrapper_rshift(object* self, object* args, object* kwargs){
    if (CAST_DICT(kwargs)->val->size()!=0){
        vm_add_err(&ValueError, vm, "Expected no keyword arguments, got %d", CAST_DICT(kwargs)->val->size());
        return NULL;
    }
    if (CAST_LIST(args)->size!=2){
        vm_add_err(&ValueError, vm, "Expected 2 arguments, got %d",CAST_LIST(args)->size);
        return NULL;
    }
    
    object* ret=CAST_TYPE(self)->slot_number->slot_rshift(list_index_int(args, 0), list_index_int(args, 1));
    if (ret==NULL){
        vm_add_err(&TypeError, vm, "Invalid operand types for >>: '%s', and '%s'.", self->type->name->c_str(), list_index_int(args, 1)->type->name->c_str());
        return NULL;
    }
    return ret;
}

object* type_wrapper_fldiv(object* self, object* args, object* kwargs){
    if (CAST_DICT(kwargs)->val->size()!=0){
        vm_add_err(&ValueError, vm, "Expected no keyword arguments, got %d", CAST_DICT(kwargs)->val->size());
        return NULL;
    }
    if (CAST_LIST(args)->size!=2){
        vm_add_err(&ValueError, vm, "Expected 2 arguments, got %d",CAST_LIST(args)->size);
        return NULL;
    }
    
    object* ret=CAST_TYPE(self)->slot_number->slot_fldiv(list_index_int(args, 0), list_index_int(args, 1));
    if (ret==NULL){
        vm_add_err(&TypeError, vm, "Invalid operand types for //: '%s', and '%s'.", self->type->name->c_str(), list_index_int(args, 1)->type->name->c_str());
        return NULL;
    }
    return ret;
}



object* type_wrapper_eq(object* self, object* args, object* kwargs){
    if (CAST_DICT(kwargs)->val->size()!=0){
        vm_add_err(&ValueError, vm, "Expected no keyword arguments, got %d", CAST_DICT(kwargs)->val->size());
        return NULL;
    }
    if (CAST_LIST(args)->size!=2){
        vm_add_err(&ValueError, vm, "Expected 2 arguments, got %d",CAST_LIST(args)->size);
        return NULL;
    }
    
    object* ret=CAST_TYPE(self)->slot_cmp(list_index_int(args, 0), list_index_int(args, 1), CMP_EQ);
    if (ret==NULL){
        vm_add_err(&TypeError, vm, "Invalid operand types for ==: '%s', and '%s'.", self->type->name->c_str(), list_index_int(args, 1)->type->name->c_str());
        return NULL;
    }
    return ret;
}

object* type_wrapper_ne(object* self, object* args, object* kwargs){
    if (CAST_DICT(kwargs)->val->size()!=0){
        vm_add_err(&ValueError, vm, "Expected no keyword arguments, got %d", CAST_DICT(kwargs)->val->size());
        return NULL;
    }
    if (CAST_LIST(args)->size!=2){
        vm_add_err(&ValueError, vm, "Expected 2 arguments, got %d",CAST_LIST(args)->size);
        return NULL;
    }
    
    object* ret=CAST_TYPE(self)->slot_cmp(list_index_int(args, 0), list_index_int(args, 1), CMP_NE);
    if (ret==NULL){
        vm_add_err(&TypeError, vm, "Invalid operand types for !=: '%s', and '%s'.", self->type->name->c_str(), list_index_int(args, 1)->type->name->c_str());
        return NULL;
    }
    return ret;
}

object* type_wrapper_gt(object* self, object* args, object* kwargs){
    if (CAST_DICT(kwargs)->val->size()!=0){
        vm_add_err(&ValueError, vm, "Expected no keyword arguments, got %d", CAST_DICT(kwargs)->val->size());
        return NULL;
    }
    if (CAST_LIST(args)->size!=2){
        vm_add_err(&ValueError, vm, "Expected 2 arguments, got %d",CAST_LIST(args)->size);
        return NULL;
    }
    
    object* ret=CAST_TYPE(self)->slot_cmp(list_index_int(args, 0), list_index_int(args, 1), CMP_GT);
    if (ret==NULL){
        vm_add_err(&TypeError, vm, "Invalid operand types for >: '%s', and '%s'.", self->type->name->c_str(), list_index_int(args, 1)->type->name->c_str());
        return NULL;
    }
    return ret;
}

object* type_wrapper_lt(object* self, object* args, object* kwargs){
    if (CAST_DICT(kwargs)->val->size()!=0){
        vm_add_err(&ValueError, vm, "Expected no keyword arguments, got %d", CAST_DICT(kwargs)->val->size());
        return NULL;
    }
    if (CAST_LIST(args)->size!=2){
        vm_add_err(&ValueError, vm, "Expected 2 arguments, got %d",CAST_LIST(args)->size);
        return NULL;
    }
    
    object* ret=CAST_TYPE(self)->slot_cmp(list_index_int(args, 0), list_index_int(args, 1), CMP_LT);
    if (ret==NULL){
        vm_add_err(&TypeError, vm, "Invalid operand types for <: '%s', and '%s'.", self->type->name->c_str(), list_index_int(args, 1)->type->name->c_str());
        return NULL;
    }
    return ret;
}

object* type_wrapper_gte(object* self, object* args, object* kwargs){
    if (CAST_DICT(kwargs)->val->size()!=0){
        vm_add_err(&ValueError, vm, "Expected no keyword arguments, got %d", CAST_DICT(kwargs)->val->size());
        return NULL;
    }
    if (CAST_LIST(args)->size!=2){
        vm_add_err(&ValueError, vm, "Expected 2 arguments, got %d",CAST_LIST(args)->size);
        return NULL;
    }
    
    object* ret=CAST_TYPE(self)->slot_cmp(list_index_int(args, 0), list_index_int(args, 1), CMP_GTE);
    if (ret==NULL){
        vm_add_err(&TypeError, vm, "Invalid operand types for >=: '%s', and '%s'.", self->type->name->c_str(), list_index_int(args, 1)->type->name->c_str());
        return NULL;
    }
    return ret;
}

object* type_wrapper_lte(object* self, object* args, object* kwargs){
    if (CAST_DICT(kwargs)->val->size()!=0){
        vm_add_err(&ValueError, vm, "Expected no keyword arguments, got %d", CAST_DICT(kwargs)->val->size());
        return NULL;
    }
    if (CAST_LIST(args)->size!=2){
        vm_add_err(&ValueError, vm, "Expected 2 arguments, got %d",CAST_LIST(args)->size);
        return NULL;
    }
    
    object* ret=CAST_TYPE(self)->slot_cmp(list_index_int(args, 0), list_index_int(args, 1), CMP_LTE);
    if (ret==NULL){
        vm_add_err(&TypeError, vm, "Invalid operand types for <=: '%s', and '%s'.", self->type->name->c_str(), list_index_int(args, 1)->type->name->c_str());
        return NULL;
    }
    return ret;
}

object* type_wrapper_in(object* self, object* args, object* kwargs){
    if (CAST_DICT(kwargs)->val->size()!=0){
        vm_add_err(&ValueError, vm, "Expected no keyword arguments, got %d", CAST_DICT(kwargs)->val->size());
        return NULL;
    }
    if (CAST_LIST(args)->size!=2){
        vm_add_err(&ValueError, vm, "Expected 2 arguments, got %d",CAST_LIST(args)->size);
        return NULL;
    }
    
    object* ret=CAST_TYPE(self)->slot_cmp(list_index_int(args, 0), list_index_int(args, 1), CMP_IN);
    if (ret==NULL){
        vm_add_err(&TypeError, vm, "Invalid operand types for in: '%s', and '%s'.", self->type->name->c_str(), list_index_int(args, 1)->type->name->c_str());
        return NULL;
    }
    return ret;
}

object* type_wrapper_call(object* self, object* args, object* kwargs){
    if (CAST_LIST(args)->size==0 && CAST_DICT(kwargs)->val->size()==0){
        vm_add_err(&ValueError, vm, "Expected at least 1 argument, got 0");
        return NULL;
    }
    
    return CAST_TYPE(self)->slot_call(list_index_int(args, 0), args, kwargs);
}

object* type_wrapper_init(object* self, object* args, object* kwargs){
    if (CAST_LIST(args)->size==0 && CAST_DICT(kwargs)->val->size()==0){
        vm_add_err(&ValueError, vm, "Expected at least 1 argument, got 0");
        return NULL;
    }
    
    return CAST_TYPE(self)->slot_init(list_index_int(args, 0), args, kwargs);
}

object* type_wrapper_iter(object* self, object* args, object* kwargs){
    if (CAST_DICT(kwargs)->val->size()!=0){
        vm_add_err(&ValueError, vm, "Expected no keyword arguments, got %d", CAST_DICT(kwargs)->val->size());
        return NULL;
    }
    if (CAST_LIST(args)->size!=1){
        vm_add_err(&ValueError, vm, "Expected 1 argument, got %d",CAST_LIST(args)->size);
        return NULL;
    }
    
    return CAST_TYPE(self)->slot_iter(list_index_int(args, 0));
}

object* type_wrapper_new(object* self, object* args, object* kwargs){
    if (CAST_LIST(args)->size==0 && CAST_DICT(kwargs)->val->size()==0){
        vm_add_err(&ValueError, vm, "Expected at least 1 argument, got 0");
        return NULL;
    }
    return CAST_TYPE(self)->slot_new(list_index_int(args, 0), args, kwargs);
}

object* type_wrapper_next(object* self, object* args, object* kwargs){
    if (CAST_LIST(args)->size==0 && CAST_DICT(kwargs)->val->size()==0){
        vm_add_err(&ValueError, vm, "Expected at least 1 argument, got  %d",CAST_LIST(args)->size+CAST_DICT(kwargs)->val->size());
        return NULL;
    }
    
    return CAST_TYPE(self)->slot_next(list_index_int(args, 0));
}

object* type_wrapper_repr(object* self, object* args, object* kwargs){
    if (CAST_DICT(kwargs)->val->size()!=0){
        vm_add_err(&ValueError, vm, "Expected no keyword arguments, got %d", CAST_DICT(kwargs)->val->size());
        return NULL;
    }
    if (CAST_LIST(args)->size!=1){
        vm_add_err(&ValueError, vm, "Expected 1 argument, got %d",CAST_LIST(args)->size);
        return NULL;
    }
    
    return CAST_TYPE(self)->slot_repr(list_index_int(args, 0));
}

object* type_wrapper_str(object* self, object* args, object* kwargs){
    if (CAST_DICT(kwargs)->val->size()!=0){
        vm_add_err(&ValueError, vm, "Expected no keyword arguments, got %d", CAST_DICT(kwargs)->val->size());
        return NULL;
    }
    if (CAST_LIST(args)->size!=1){
        vm_add_err(&ValueError, vm, "Expected 1 argument, got %d",CAST_LIST(args)->size);
        return NULL;
    }
    
    return CAST_TYPE(self)->slot_str(list_index_int(args, 0));
}

object* type_wrapper_descrget(object* self, object* args, object* kwargs){
    BigInt len=CAST_LIST(args)->size;
    if ((len!=2 && len!=3) || CAST_DICT(kwargs)->val->size()!=0){
        vm_add_err(&ValueError, vm, "Expected 2 or 3 arguments, got %d",CAST_LIST(args)->size+CAST_DICT(kwargs)->val->size());
        return NULL;
    }
    if (len==3){
        return CAST_TYPE(self)->slot_descrget(list_index_int(args, 0), list_index_int(args, 1), list_index_int(args, 2));
    }
    return CAST_TYPE(self)->slot_descrget(list_index_int(args, 0), list_index_int(args, 1), NULL);
}

object* type_wrapper_descrset(object* self, object* args, object* kwargs){
    if (CAST_LIST(args)->size!=3 || CAST_DICT(kwargs)->val->size()!=0){
        vm_add_err(&ValueError, vm, "Expected 3 arguments, got %d",CAST_LIST(args)->size+CAST_DICT(kwargs)->val->size());
        return NULL;
    }

    object* v=list_index_int(args, 2);
    if (object_istype(v->type, &NoneType)){
        return CAST_TYPE(self)->slot_descrset(list_index_int(args, 0), list_index_int(args, 1), NULL);
    }
    
    return CAST_TYPE(self)->slot_descrset(list_index_int(args, 0), list_index_int(args, 1), v);
}

object* type_wrapper_getattr(object* self, object* args, object* kwargs){
    if (CAST_DICT(kwargs)->val->size()!=0){
        vm_add_err(&ValueError, vm, "Expected no keyword arguments, got %d", CAST_DICT(kwargs)->val->size());
        return NULL;
    }
    if (CAST_LIST(args)->size!=2){
        vm_add_err(&ValueError, vm, "Expected 2 arguments, got %d",CAST_LIST(args)->size);
        return NULL;
    }
    
    return CAST_TYPE(self)->slot_getattr(list_index_int(args, 0), list_index_int(args, 1));
}

object* type_wrapper_setattr(object* self, object* args, object* kwargs){
    if (CAST_LIST(args)->size!=3 || CAST_DICT(kwargs)->val->size()!=0){
        vm_add_err(&ValueError, vm, "Expected 3 arguments, got %d",CAST_LIST(args)->size+CAST_DICT(kwargs)->val->size());
        return NULL;
    }

    object* v=list_index_int(args, 2);
    if (object_istype(v->type, &NoneType)){
        return CAST_TYPE(self)->slot_setattr(list_index_int(args, 0), list_index_int(args, 1), NULL);
    }
    
    return CAST_TYPE(self)->slot_setattr(list_index_int(args, 0), list_index_int(args, 1), v);
}

object* type_wrapper_del(object* self, object* args, object* kwargs){
    if (CAST_DICT(kwargs)->val->size()!=0){
        vm_add_err(&ValueError, vm, "Expected no keyword arguments, got %d", CAST_DICT(kwargs)->val->size());
        return NULL;
    }
    if (CAST_LIST(args)->size!=1){
        vm_add_err(&ValueError, vm, "Expected 1 argument, got %d",CAST_LIST(args)->size);
        return NULL;
    }
    
    CAST_TYPE(self)->slot_del(list_index_int(args, 0));
    return new_none();
}

object* type_wrapper_enter(object* self, object* args, object* kwargs){
    if (CAST_DICT(kwargs)->val->size()!=0){
        vm_add_err(&ValueError, vm, "Expected no keyword arguments, got %d", CAST_DICT(kwargs)->val->size());
        return NULL;
    }
    if (CAST_LIST(args)->size!=1){
        vm_add_err(&ValueError, vm, "Expected 1 argument, got %d",CAST_LIST(args)->size);
        return NULL;
    }
    
    return CAST_TYPE(self)->slot_enter(list_index_int(args, 0));
}

object* type_wrapper_exit(object* self, object* args, object* kwargs){
    if (CAST_DICT(kwargs)->val->size()!=0){
        vm_add_err(&ValueError, vm, "Expected no keyword arguments, got %d", CAST_DICT(kwargs)->val->size());
        return NULL;
    }
    if (CAST_LIST(args)->size!=1){
        vm_add_err(&ValueError, vm, "Expected 1 argument, got %d",CAST_LIST(args)->size);
        return NULL;
    }
    
    return CAST_TYPE(self)->slot_exit(list_index_int(args, 0));
}

object* type_wrapper_abs(object* self, object* args, object* kwargs){
    if (CAST_DICT(kwargs)->val->size()!=0){
        vm_add_err(&ValueError, vm, "Expected no keyword arguments, got %d", CAST_DICT(kwargs)->val->size());
        return NULL;
    }
    if (CAST_LIST(args)->size!=1){
        vm_add_err(&ValueError, vm, "Expected 1 argument, got %d",CAST_LIST(args)->size);
        return NULL;
    }
    
    object* ret=CAST_TYPE(self)->slot_number->slot_abs(list_index_int(args, 0));
    if (ret==NULL){
        vm_add_err(&TypeError, vm, "Invalid operand type for absolute value: '%s'.",  list_index_int(args, 0)->type->name->c_str());
        return NULL;
    }
    return ret;
}

object* type_wrapper_not(object* self, object* args, object* kwargs){
    if (CAST_DICT(kwargs)->val->size()!=0){
        vm_add_err(&ValueError, vm, "Expected no keyword arguments, got %d", CAST_DICT(kwargs)->val->size());
        return NULL;
    }
    if (CAST_LIST(args)->size!=1){
        vm_add_err(&ValueError, vm, "Expected 1 argument, got %d",CAST_LIST(args)->size);
        return NULL;
    }
    
    object* ret=CAST_TYPE(self)->slot_number->slot_not(list_index_int(args, 0));
    if (ret==NULL){
        vm_add_err(&TypeError, vm, "Invalid operand type for ~: '%s'.",  list_index_int(args, 0)->type->name->c_str());
        return NULL;
    }
    return ret;
}