#include <cyaml/cyaml.h>
#include <stdio.h>
#include "command.h"
#include "cyaml-defs.h"
#include "targets.h"

int genBuild(int argc, char const *argv[]) {
	struct build_config *config;
	cyaml_err_t err;
	register int i;
	int res;
	char tmp[80];
	puts("\e[1;32mLoading \e[0;31mbuildconf.yml\e[1;32m...\e[0m");
	err = cyaml_load_file("buildconf.yml", &cyconfig,
			&config_schema, (void **) &config, NULL);

	if(err != CYAML_OK) {
		printf("\e[1;31mError:\e[0;31m %s\e[0m\n", cyaml_strerror(err));
		return 1;
	}
	if(argc < 2) {
		printf("\e[1;32mRunning default task: \e[0;31m%s\e[0m\n", config->defaultStep);
		return runDefault(config);
	} else {
		printf("\e[1;32mRunning tasks: \e[0;31m");
		for(i = 1; i < argc; i++) {
			printf("%s ", argv[i]);
		}
		printf("\e[0m\n");
		for(i = 1; i < argc; i++) {
			if(hasStep(config, argv[i])) {
				res = runStep(config, argv[i]);
				if (res != 0) {
					printf("\e[1;31mError:\e[0;31m Target %s failed with %i\e[0m\n", argv[i], res);
					return res;
				}
			} else {
				printf("\e[1;31mError:\e[0;31m No such target: %s\e[0m\n", argv[i]);
				return 1;
			}
		}
	}
};

int listTargets() {
	struct build_config *config;
	cyaml_err_t err;
	register int i;

	err = cyaml_load_file("buildconf.yml", &cyconfig,
			&config_schema, (void **) &config, NULL);

	if(err != CYAML_OK) {
		printf("\e[1;31mError:\e[0;31m %s\e[0m\n", cyaml_strerror(err));
		return 1;
	}
	printf("\e[1;31mDefault task: \e[0;33m%s\e[0m\n", config->defaultStep);
	for(i = 0; i < config->steps_count; i++) {
		printf("\e[1;32m%s: \e[0;33m%s\e[0m\n", config->steps[i]->name, config->steps[i]->description);
	}
	return 0;
}
