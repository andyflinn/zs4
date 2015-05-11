##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=zs4
ConfigurationName      :=Debug
WorkspacePath          := "/home/countinn/zs4/codelite"
ProjectPath            := "/home/countinn/zs4/codelite"
IntermediateDirectory  :=$(WorkspacePath)/../../int/$(ConfigurationName)/$(ProjectName)/
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=countinn
Date                   :=05/10/2015
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
OutputFile             :=$(WorkspacePath)/../../bin/$(ConfigurationName)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E 
ObjectsFileList        :="zs4.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). $(IncludeSwitch)../include 
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
CXXFLAGS :=  -g -O0 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/zs4_main$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

$(IntermediateDirectory)/.d:
	@test -d $(WorkspacePath)/../../int/$(ConfigurationName)/$(ProjectName)/ || $(MakeDirCommand) $(WorkspacePath)/../../int/$(ConfigurationName)/$(ProjectName)/

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/zs4_main$(ObjectSuffix): ../zs4/main.cpp $(IntermediateDirectory)/zs4_main$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/countinn/zs4/zs4/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/zs4_main$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/zs4_main$(DependSuffix): ../zs4/main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/zs4_main$(ObjectSuffix) -MF$(IntermediateDirectory)/zs4_main$(DependSuffix) -MM "../zs4/main.cpp"

$(IntermediateDirectory)/zs4_main$(PreprocessSuffix): ../zs4/main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/zs4_main$(PreprocessSuffix) "../zs4/main.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/zs4_main$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/zs4_main$(DependSuffix)
	$(RM) $(IntermediateDirectory)/zs4_main$(PreprocessSuffix)
	$(RM) $(OutputFile)
	$(RM) ".build-debug/zs4"


