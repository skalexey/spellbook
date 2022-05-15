from build_utils import *
import sys

if (len(buildFolder) > 0):
	removeDir("../vl_cpp_generator/" + buildConfigFolder)
	removeDir("../DataModelBuilder/Core/" + buildConfigFolder)
	removeDir("../JSONConverter/" + buildConfigFolder)
	removeDir("../VL/" + buildConfigFolder)

