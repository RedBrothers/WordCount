#include "wordcount/base_manager.h"
#include "utils.h"

void BaseManager::save() {
    auto wc_by_a = sort_by_a(wc);
    save_dict(out_by_a_, wc_by_a);
    auto wc_by_n = sort_by_n(wc);
    save_dict(out_by_n_, wc_by_n);
}


