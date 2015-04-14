##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=zs4dyad
ConfigurationName      :=Debug
WorkspacePath          := "/home/countinn/zs4"
ProjectPath            := "/home/countinn/zs4/zs4dyad"
IntermediateDirectory  :=../../int/linux/$(ConfigurationName)/$(ProjectName)/
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=countinn
Date                   :=04/13/2015
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
OutputFile             :=../../bin/linux/$(ConfigurationName)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E 
ObjectsFileList        :="zs4dyad.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). $(IncludeSwitch)../include/ 
IncludePCH             := 
RcIncludePath          := 
Libs                   := $(LibrarySwitch)m $(LibrarySwitch)c $(LibrarySwitch)openssl $(LibrarySwitch)zs4static 
ArLibs                 :=  "m" "c" "openssl" "zs4static" 
LibPath                := $(LibraryPathSwitch). $(LibraryPathSwitch)../../bin/linux/$(ConfigurationName)/ 

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
Objects0=$(IntermediateDirectory)/main$(ObjectSuffix) $(IntermediateDirectory)/dyad$(ObjectSuffix) $(IntermediateDirectory)/zs4dyad$(ObjectSuffix) 



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
	@test -d ../../int/linux/$(ConfigurationName)/$(ProjectName)/ || $(MakeDirCommand) ../../int/linux/$(ConfigurationName)/$(ProjectName)/

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/main$(ObjectSuffix): main.cpp $(IntermediateDirectory)/main$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/countinn/zs4/zs4dyad/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main$(DependSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main$(ObjectSuffix) -MF$(IntermediateDirectory)/main$(DependSuffix) -MM "main.cpp"

$(IntermediateDirectory)/main$(PreprocessSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main$(PreprocessSuffix) "main.cpp"

$(IntermediateDirectory)/dyad$(ObjectSuffix): dyad.c $(IntermediateDirectory)/dyad$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/countinn/zs4/zs4dyad/dyad.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/dyad$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/dyad$(DependSuffix): dyad.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/dyad$(ObjectSuffix) -MF$(IntermediateDirectory)/dyad$(DependSuffix) -MM "dyad.c"

$(IntermediateDirectory)/dyad$(PreprocessSuffix): dyad.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/dyad$(PreprocessSuffix) "dyad.c"

$(IntermediateDirectory)/zs4dyad$(ObjectSuffix): zs4dyad.cpp $(IntermediateDirectory)/zs4dyad$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/countinn/zs4/zs4dyad/zs4dyad.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/zs4dyad$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/zs4dyad$(DependSuffix): zs4dyad.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/zs4dyad$(ObjectSuffix) -MF$(IntermediateDirectory)/zs4dyad$(DependSuffix) -MM "zs4dyad.cpp"

$(IntermediateDirectory)/zs4dyad$(PreprocessSuffix): zs4dyad.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/zs4dyad$(PreprocessSuffix) "zs4dyad.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/main$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/main$(DependSuffix)
	$(RM) $(IntermediateDirectory)/main$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/dyad$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/dyad$(DependSuffix)
	$(RM) $(IntermediateDirectory)/dyad$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/zs4dyad$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/zs4dyad$(DependSuffix)
	$(RM) $(IntermediateDirectory)/zs4dyad$(PreprocessSuffix)
	$(RM) $(OutputFile)
	$(RM) "../.build-debug/zs4dyad"


