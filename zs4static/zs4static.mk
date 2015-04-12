##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=zs4static
ConfigurationName      :=Debug
WorkspacePath          := "/home/countinn/zs4"
ProjectPath            := "/home/countinn/zs4/zs4static"
IntermediateDirectory  :=../../int/linux/$(ConfigurationName)/$(ProjectName)/
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=countinn
Date                   :=04/12/2015
CodeLitePath           :="/home/countinn/.codelite"
LinkerName             :=g++
SharedObjectLinkerName :=g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.o.i
DebugSwitch            :=-gstab
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=../../bin/linux/$(ConfigurationName)/lib$(ProjectName).a
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E 
ObjectsFileList        :="zs4static.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). $(IncludeSwitch)../include/ 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := ar rcus
CXX      := g++
CC       := gcc
CXXFLAGS :=  -g $(Preprocessors)
CFLAGS   :=  -g $(Preprocessors)


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/zs4ssl$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild
all: $(IntermediateDirectory) $(OutputFile)

$(OutputFile): $(Objects)
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(AR) $(ArchiveOutputSwitch)$(OutputFile) @$(ObjectsFileList) $(ArLibs)
	@$(MakeDirCommand) "/home/countinn/zs4/.build-debug"
	@echo rebuilt > "/home/countinn/zs4/.build-debug/zs4static"

../../int/linux/$(ConfigurationName)/$(ProjectName)/:
	@test -d ../../int/linux/$(ConfigurationName)/$(ProjectName)/ || $(MakeDirCommand) ../../int/linux/$(ConfigurationName)/$(ProjectName)/

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/zs4ssl$(ObjectSuffix): zs4ssl.cpp $(IntermediateDirectory)/zs4ssl$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/countinn/zs4/zs4static/zs4ssl.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/zs4ssl$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/zs4ssl$(DependSuffix): zs4ssl.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/zs4ssl$(ObjectSuffix) -MF$(IntermediateDirectory)/zs4ssl$(DependSuffix) -MM "zs4ssl.cpp"

$(IntermediateDirectory)/zs4ssl$(PreprocessSuffix): zs4ssl.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/zs4ssl$(PreprocessSuffix) "zs4ssl.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/zs4ssl$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/zs4ssl$(DependSuffix)
	$(RM) $(IntermediateDirectory)/zs4ssl$(PreprocessSuffix)
	$(RM) $(OutputFile)
	$(RM) "../.build-debug/zs4static"


