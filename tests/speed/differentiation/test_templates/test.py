#!usr/bin/python3
#test.py
import random
import time
import subprocess
import logging
from test_templates.create_function import create_function

def run_test(args, include, include_number,
        gsl_function_call, gsl_function_call_number,
        numpp_function_call, numpp_function_call_number,
        test_function_number_gsl, test_function_number_numpp,
        log_name
        ):
    """
    Inserts values into template and executes cpp test
    See template to grasp arguments better
    expressions_count - maximum number of expressions in generated mathemathical
    functions
    This way is supposedly the fastest
    """

    with open(args.template, "r") as template:
        template_content=template.readlines()
        template_content[include_number]=include
        #LOGGING
        logging.basicConfig(filename=log_name,level=logging.DEBUG)

        for i in range(0, int(args.cases)):
            function = create_function(args.expressions, args.low, args.high)
            template_content[test_function_number_gsl] = function
            template_content[test_function_number_numpp] = function

            function_argument = round(random.uniform(float(args.arglow),
                float(args.arghigh)), 4)

            template_content[gsl_function_call_number] = "%s %s %s" % \
            (gsl_function_call, function_argument, ", 1e-8, &result_gsl, &abserr);")

            template_content[numpp_function_call_number] = "%s %s %s" % \
            (numpp_function_call, function_argument, ", 1e-8);")

            with open("./differentiation/temp_test.cpp", "w+") as test:
                test.writelines(template_content)
            compilation_status = subprocess.run(["g++",
                "../utilities/tests_main.o",
                "./differentiation/temp_test.cpp", "-o", "./differentiation/temp_test", "-lgsl","-lgslcblas", "-lm"])
            if compilation_status.returncode == 0:
                test_status = subprocess.run(["./differentiation/temp_test"])
            else:
                logging.warning("Compilation failed for function:\n" +  function)


