object* type_new(object* type, object* args, object* kwargs);
void type_del(object* self);
object* type_repr(object* self);
object* type_cmp(object* self, object* other, uint8_t type);
object* type_call(object* self, object* args, object* kwargs);
object* type_get(object* self, object* attr);
void type_set(object* obj, object* attr, object* val);
object* type_bool(object* self);

static NumberMethods type_num_methods{
    0, //slot_add
    0, //slot_sub
    0, //slot_mul
    0, //slot_div
    0, //slot_mod
    0, //slot_pow
    0, //slot_and
    0, //slot_or
    0, //slot_lshift
    0, //slot_rshift
    0, //slot_fldiv
    0, //slot_xor

    0, //slot_neg
    0, //slot_not
    0, //slot_abs

    (unaryfunc)type_bool, //slot_bool
};

static Mappings type_mappings{
    0, //slot_get
    0, //slot_set
    0, //slot_len
};

object* type_dict(object* type);
object* type_bases_get(object* type);
object* type_doc_get(object* type);

Method type_methods[]={{NULL,NULL}};
GetSets type_getsets[]={{NULL,NULL}};
OffsetMember type_offsets[]={{NULL}};

TypeObject TypeType={
    0, //refcnt
    0, //ob_prev
    0, //ob_next
    0, //gen
    &TypeType, //type
    new string("type"), //name
    sizeof(TypeObject), //size
    0, //var_base_size
    false, //gc_trackable
    NULL, //bases
    offsetof(TypeObject, dict), //dict_offset
    NULL, //dict
    (getattrfunc)type_get, //slot_getattr
    (setattrfunc)type_set, //slot_getattr

    0, //slot_init
    (newfunc)type_new, //slot_new
    (delfunc)type_del, //slot_del

    0, //slot_next
    0, //slot_iter

    (reprfunc)type_repr, //slot_repr
    (reprfunc)type_repr, //slot_str
    (callfunc)type_call, //slot_call

    &type_num_methods, //slot_number
    &type_mappings, //slot_mapping

    type_methods, //slot_methods
    type_getsets, //slot_getsets
    type_offsets, //slot_offsests

    0, //slot_cmp
};


object* newtp_init(object* self, object* args, object* kwargs);
object* newtp_new(object* self, object* args, object* kwargs);
void newtp_del(object* self);
void _newtp_del(object* self);
object* newtp_next(object* self);
object* newtp_get(object* self, object* idx);
object* newtp_len(object* self);
object* newtp_set(object* self, object* idx, object* val);
object* newtp_repr(object* self);
object* newtp_str(object* self);
object* newtp_call(object* self, object* args, object* kwargs);
object* newtp_cmp(object* self, object* other, uint8_t type);
object* newtp_iter(object* self);

object* newtp_add(object* self, object* other);
object* newtp_sub(object* self, object* other);
object* newtp_mul(object* self, object* other);
object* newtp_div(object* self, object* other);
object* newtp_mod(object* self, object* other);
object* newtp_pow(object* self, object* other);
object* newtp_and(object* self, object* other);
object* newtp_or(object* self, object* other);
object* newtp_lshift(object* self, object* other);
object* newtp_rshift(object* self, object* other);
object* newtp_fldiv(object* self, object* other);
object* newtp_xor(object* self, object* other);

object* newtp_neg(object* self);
object* newtp_not(object* self);
object* newtp_bool(object* self);
object* newtp_int(object* self);
object* newtp_float(object* self);
void newtp_post_tpcall(object* ob);
object* newtp_abs(object* self);

object* newtp_descrget(object* obj, object* self, object* owner);
object* newtp_descrset(object* obj, object* self, object* val);

object* newtp_getattr(object* self, object* attr);
object* newtp_setattr(object* self, object* attr, object* val);

object* newtp_enter(object* self);
object* newtp_exit(object* self);

NumberMethods newtp_number={    
    //binops
    newtp_add,
    newtp_sub,
    newtp_mul,
    newtp_div,
    newtp_mod,
    newtp_pow,
    newtp_and,
    newtp_or,
    newtp_lshift,
    newtp_rshift,
    newtp_fldiv,
    newtp_xor,

    //unaryops
    newtp_neg,
    newtp_not,
    newtp_abs,

    //other
    newtp_bool,
    newtp_int,
    newtp_float,
};

typedef struct NewTypeObject{
    OBJHEAD_EXTRA;
    object* dict;
}NewTypeObject;

static Mappings newtp_mappings{
    newtp_get, //slot_get
    newtp_set, //slot_set
    newtp_len, //slot_len
};

Method newtp_methods[]={{NULL,NULL}};
GetSets newtp_getsets[]={{NULL,NULL}};
OffsetMember newtp_offsets[]={{"__dict__", 0, true}, {NULL}};

#define CAST_NEWTYPE(obj) ((NewTypeObject*)(obj))

object* new_type(string* name, object* bases, object* dict, object* doc);

object* type_new(object* type, object* args, object* kwargs);
void type_del(object* self);
object* type_repr(object* self);
object* type_cmp(object* self, object* other, uint8_t type);
object* type_call(object* self, object* args, object* kwargs);
void setup_type_type(){
    TypeType=(*(TypeObject*)finalize_type(&TypeType));
    fplbases.push_back(&TypeType);
}
