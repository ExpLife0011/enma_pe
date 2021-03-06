#pragma once

#define ALIGN_UP(a, b) (((a + b - 1) / b) * b)

#ifndef max
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#endif

#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif

#include "enma_pe_internal.h"
#include "pe_image.h"

enum directory_placment_id {
    dp_id_export_desc,
    dp_id_export_func_table,
    dp_id_export_name_table,
    dp_id_export_ordinal_table,
    dp_id_export_names,

    dp_id_import_desc,
    dp_id_import_oft,
    dp_id_import_iat,
    dp_id_import_names,

    dp_id_resources_desc,

    dp_id_exceptions_desc,

    dp_id_security_desc,

    dp_id_relocations_desc,

    dp_id_debug_desc,
    dp_id_debug_item_data,
    
    dp_id_tls_desc,
    dp_id_tls_raw_data,
    dp_id_tls_index,
    dp_id_tls_callbacks,

    dp_id_loadconfig_desc,
    dp_id_loadconfig_se_table,
    dp_id_loadconfig_cf_table,


    dp_id_bound_import_desc,
    dp_id_bound_import_ref_desc,
    dp_id_bound_import_names,

    dp_id_delay_import,
};

struct directory_placement {
    uint32_t rva; 
    size_t size; 
    directory_placment_id id;
};

enum directory_code {
    directory_code_success,
    directory_code_not_present,
    directory_code_partially_initialized,
    directory_code_bad,
};

#include "pe_export.h"
#include "pe_bound_import.h"
#include "pe_import.h"
#include "pe_resources.h"
#include "pe_exceptions.h"
#include "pe_security.h"
#include "pe_relocations.h"
#include "pe_debug.h"
#include "pe_tls.h"
#include "pe_loadconfig.h"
#include "pe_delay_import.h"
#include "pe_dotnet.h"

struct pe_image_expanded {
    directory_code code;
    
    export_table        exports;
    import_table        imports;
    resource_directory  resources;
    exceptions_table    exceptions;
    relocation_table    relocations;
    debug_table         debug;
    tls_table           tls;
    load_config_table   load_config;
    delay_import_table  delay_imports;
    bound_import_table  bound_imports;

    pe_image image;

    pe_image_expanded::pe_image_expanded();
    pe_image_expanded::pe_image_expanded(const pe_image_expanded& image_ex);
    pe_image_expanded& pe_image_expanded::operator=(const pe_image_expanded& image_ex);
};


void do_expanded_pe_image(_Inout_ pe_image_expanded& expanded_image, _In_ const pe_image &image);
directory_code get_directories_placement(_Inout_ pe_image &image, _Out_ std::vector<directory_placement>& placement);

void erase_directories_placement(_Inout_ pe_image &image, _In_ std::vector<directory_placement>& placement,
    _Inout_opt_ relocation_table* relocs = 0,_In_opt_ bool delete_empty_sections = false);




#include "pe_helper.h"