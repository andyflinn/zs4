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
Date                   :=04/15/2015
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
Objects0=$(IntermediateDirectory)/zs4crypt$(ObjectSuffix) $(IntermediateDirectory)/zs4fs$(ObjectSuffix) 



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
$(IntermediateDirectory)/zs4crypt$(ObjectSuffix): zs4crypt.cpp $(IntermediateDirectory)/zs4crypt$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/countinn/zs4/zs4static/zs4crypt.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/zs4crypt$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/zs4crypt$(DependSuffix): zs4crypt.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/zs4crypt$(ObjectSuffix) -MF$(IntermediateDirectory)/zs4crypt$(DependSuffix) -MM "zs4crypt.cpp"

$(IntermediateDirectory)/zs4crypt$(PreprocessSuffix): zs4crypt.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/zs4crypt$(PreprocessSuffix) "zs4crypt.cpp"

$(IntermediateDirectory)/zs4fs$(ObjectSuffix): zs4fs.cpp $(IntermediateDirectory)/zs4fs$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/countinn/zs4/zs4static/zs4fs.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/zs4fs$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/zs4fs$(DependSuffix): zs4fs.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/zs4fs$(ObjectSuffix) -MF$(IntermediateDirectory)/zs4fs$(DependSuffix) -MM "zs4fs.cpp"

$(IntermediateDirectory)/zs4fs$(PreprocessSuffix): zs4fs.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/zs4fs$(PreprocessSuffix) "zs4fs.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/zs4crypt$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/zs4crypt$(DependSuffix)
	$(RM) $(IntermediateDirectory)/zs4crypt$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/zs4fs$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/zs4fs$(DependSuffix)
	$(RM) $(IntermediateDirectory)/zs4fs$(PreprocessSuffix)
	$(RM) $(OutputFile)
	$(RM) "../.build-debug/zs4static"


