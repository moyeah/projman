#ifndef __H_NEWPROJECTGDA__
#define __H_NEWPROJECTGDA__

typedef struct {
        gchar *name;
        gchar *description;
        gchar *customer;
} ProjectInfo;

int create_project (ProjectInfo *project_info);

#endif
