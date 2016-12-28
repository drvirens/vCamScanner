
#ifndef __MAIN_APP_H__
#define __MAIN_APP_H__

typedef struct _app_data app_data;

/*
 * @brief Create application instance
 * @return Application instance on success, otherwise NULL
 */
app_data *app_create();

/*
 * @brief Destroy application instance
 * @param[in]   app     Application instance
 */
void app_destroy(app_data *app);

/*
 * @brief Run Tizen application
 * @param[in]   app     Application instance
 * @param[in]   argc    argc paremeter received in main
 * @param[in]   argv    argv parameter received in main
 */
int app_run(app_data *app, int argc, char **argv);

#endif /* __MAIN_APP_H__ */
