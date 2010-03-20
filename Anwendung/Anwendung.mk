##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Release
ProjectName            :=Anwendung
ConfigurationName      :=Release
IntermediateDirectory  :=./Release
OutDir                 := $(IntermediateDirectory)
WorkspacePath          := "/media/3A64CC8964CC48F9/Projekte/Artikelverwaltung"
ProjectPath            := "/media/3A64CC8964CC48F9/Projekte/Artikelverwaltung/Anwendung"
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Jan Menzel
Date                   :=18.03.2010
CodeLitePath           :="/home/jmenzel/.codelite"
LinkerName             :=g++
ArchiveTool            :=ar rcus
SharedObjectLinkerName :=g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=
DebugSwitch            :=-gstab
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
CompilerName           :=g++
C_CompilerName         :=gcc
OutputFile             :=$(IntermediateDirectory)/Artikelverwaltung
Preprocessors          :=$(PreprocessorSwitch)__WX__ 
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=
MakeDirCommand         :=mkdir -p
CmpOptions             := -O2 $(shell wx-config --cxxflags --unicode=yes --debug=no) $(Preprocessors)
LinkOptions            :=  $(shell wx-config --debug=no --libs --unicode=yes) -s
IncludePath            :=  "$(IncludeSwitch)." 
RcIncludePath          :=
Libs                   :=$(LibrarySwitch)pq 
LibPath                := "$(LibraryPathSwitch)." 


##
## User defined environment variables
##
Objects=$(IntermediateDirectory)/main$(ObjectSuffix) $(IntermediateDirectory)/artikelpanel$(ObjectSuffix) $(IntermediateDirectory)/herstellerpanel$(ObjectSuffix) $(IntermediateDirectory)/lieferantpanel$(ObjectSuffix) $(IntermediateDirectory)/settingspanel$(ObjectSuffix) $(IntermediateDirectory)/artikeledit$(ObjectSuffix) $(IntermediateDirectory)/artikellieferantconnect$(ObjectSuffix) $(IntermediateDirectory)/herstelleradd$(ObjectSuffix) $(IntermediateDirectory)/herstelleredit$(ObjectSuffix) $(IntermediateDirectory)/lieferantadd$(ObjectSuffix) \
	$(IntermediateDirectory)/lieferantartikelconnect$(ObjectSuffix) $(IntermediateDirectory)/lieferantedit$(ObjectSuffix) $(IntermediateDirectory)/artikeladd$(ObjectSuffix) $(IntermediateDirectory)/artikeldetail$(ObjectSuffix) $(IntermediateDirectory)/herstellerdetail$(ObjectSuffix) $(IntermediateDirectory)/lieferantdetail$(ObjectSuffix) $(IntermediateDirectory)/mainwindow$(ObjectSuffix) $(IntermediateDirectory)/configurationmanager$(ObjectSuffix) $(IntermediateDirectory)/postgresql_connector$(ObjectSuffix) $(IntermediateDirectory)/dbcommand$(ObjectSuffix) \
	$(IntermediateDirectory)/dbconnectionmanager$(ObjectSuffix) $(IntermediateDirectory)/pq_multithread_wrapper$(ObjectSuffix) $(IntermediateDirectory)/updatedaemon$(ObjectSuffix) 

##
## Main Build Targets 
##
all: $(OutputFile)

$(OutputFile): makeDirStep $(Objects)
	@$(MakeDirCommand) $(@D)
	$(LinkerName) $(OutputSwitch)$(OutputFile) $(Objects) $(LibPath) $(Libs) $(LinkOptions)

makeDirStep:
	@test -d ./Release || $(MakeDirCommand) ./Release

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/main$(ObjectSuffix): main.cpp $(IntermediateDirectory)/main$(DependSuffix)
	@test -d ./Release || $(MakeDirCommand) ./Release
	$(CompilerName) $(SourceSwitch) "/media/3A64CC8964CC48F9/Projekte/Artikelverwaltung/Anwendung/main.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/main$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main$(DependSuffix): main.cpp
	@test -d ./Release || $(MakeDirCommand) ./Release
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/main$(ObjectSuffix) -MF$(IntermediateDirectory)/main$(DependSuffix) -MM "/media/3A64CC8964CC48F9/Projekte/Artikelverwaltung/Anwendung/main.cpp"

$(IntermediateDirectory)/artikelpanel$(ObjectSuffix): artikelpanel.cpp $(IntermediateDirectory)/artikelpanel$(DependSuffix)
	@test -d ./Release || $(MakeDirCommand) ./Release
	$(CompilerName) $(SourceSwitch) "/media/3A64CC8964CC48F9/Projekte/Artikelverwaltung/Anwendung/artikelpanel.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/artikelpanel$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/artikelpanel$(DependSuffix): artikelpanel.cpp
	@test -d ./Release || $(MakeDirCommand) ./Release
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/artikelpanel$(ObjectSuffix) -MF$(IntermediateDirectory)/artikelpanel$(DependSuffix) -MM "/media/3A64CC8964CC48F9/Projekte/Artikelverwaltung/Anwendung/artikelpanel.cpp"

$(IntermediateDirectory)/herstellerpanel$(ObjectSuffix): herstellerpanel.cpp $(IntermediateDirectory)/herstellerpanel$(DependSuffix)
	@test -d ./Release || $(MakeDirCommand) ./Release
	$(CompilerName) $(SourceSwitch) "/media/3A64CC8964CC48F9/Projekte/Artikelverwaltung/Anwendung/herstellerpanel.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/herstellerpanel$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/herstellerpanel$(DependSuffix): herstellerpanel.cpp
	@test -d ./Release || $(MakeDirCommand) ./Release
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/herstellerpanel$(ObjectSuffix) -MF$(IntermediateDirectory)/herstellerpanel$(DependSuffix) -MM "/media/3A64CC8964CC48F9/Projekte/Artikelverwaltung/Anwendung/herstellerpanel.cpp"

$(IntermediateDirectory)/lieferantpanel$(ObjectSuffix): lieferantpanel.cpp $(IntermediateDirectory)/lieferantpanel$(DependSuffix)
	@test -d ./Release || $(MakeDirCommand) ./Release
	$(CompilerName) $(SourceSwitch) "/media/3A64CC8964CC48F9/Projekte/Artikelverwaltung/Anwendung/lieferantpanel.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/lieferantpanel$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/lieferantpanel$(DependSuffix): lieferantpanel.cpp
	@test -d ./Release || $(MakeDirCommand) ./Release
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/lieferantpanel$(ObjectSuffix) -MF$(IntermediateDirectory)/lieferantpanel$(DependSuffix) -MM "/media/3A64CC8964CC48F9/Projekte/Artikelverwaltung/Anwendung/lieferantpanel.cpp"

$(IntermediateDirectory)/settingspanel$(ObjectSuffix): settingspanel.cpp $(IntermediateDirectory)/settingspanel$(DependSuffix)
	@test -d ./Release || $(MakeDirCommand) ./Release
	$(CompilerName) $(SourceSwitch) "/media/3A64CC8964CC48F9/Projekte/Artikelverwaltung/Anwendung/settingspanel.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/settingspanel$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/settingspanel$(DependSuffix): settingspanel.cpp
	@test -d ./Release || $(MakeDirCommand) ./Release
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/settingspanel$(ObjectSuffix) -MF$(IntermediateDirectory)/settingspanel$(DependSuffix) -MM "/media/3A64CC8964CC48F9/Projekte/Artikelverwaltung/Anwendung/settingspanel.cpp"

$(IntermediateDirectory)/artikeledit$(ObjectSuffix): artikeledit.cpp $(IntermediateDirectory)/artikeledit$(DependSuffix)
	@test -d ./Release || $(MakeDirCommand) ./Release
	$(CompilerName) $(SourceSwitch) "/media/3A64CC8964CC48F9/Projekte/Artikelverwaltung/Anwendung/artikeledit.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/artikeledit$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/artikeledit$(DependSuffix): artikeledit.cpp
	@test -d ./Release || $(MakeDirCommand) ./Release
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/artikeledit$(ObjectSuffix) -MF$(IntermediateDirectory)/artikeledit$(DependSuffix) -MM "/media/3A64CC8964CC48F9/Projekte/Artikelverwaltung/Anwendung/artikeledit.cpp"

$(IntermediateDirectory)/artikellieferantconnect$(ObjectSuffix): artikellieferantconnect.cpp $(IntermediateDirectory)/artikellieferantconnect$(DependSuffix)
	@test -d ./Release || $(MakeDirCommand) ./Release
	$(CompilerName) $(SourceSwitch) "/media/3A64CC8964CC48F9/Projekte/Artikelverwaltung/Anwendung/artikellieferantconnect.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/artikellieferantconnect$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/artikellieferantconnect$(DependSuffix): artikellieferantconnect.cpp
	@test -d ./Release || $(MakeDirCommand) ./Release
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/artikellieferantconnect$(ObjectSuffix) -MF$(IntermediateDirectory)/artikellieferantconnect$(DependSuffix) -MM "/media/3A64CC8964CC48F9/Projekte/Artikelverwaltung/Anwendung/artikellieferantconnect.cpp"

$(IntermediateDirectory)/herstelleradd$(ObjectSuffix): herstelleradd.cpp $(IntermediateDirectory)/herstelleradd$(DependSuffix)
	@test -d ./Release || $(MakeDirCommand) ./Release
	$(CompilerName) $(SourceSwitch) "/media/3A64CC8964CC48F9/Projekte/Artikelverwaltung/Anwendung/herstelleradd.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/herstelleradd$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/herstelleradd$(DependSuffix): herstelleradd.cpp
	@test -d ./Release || $(MakeDirCommand) ./Release
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/herstelleradd$(ObjectSuffix) -MF$(IntermediateDirectory)/herstelleradd$(DependSuffix) -MM "/media/3A64CC8964CC48F9/Projekte/Artikelverwaltung/Anwendung/herstelleradd.cpp"

$(IntermediateDirectory)/herstelleredit$(ObjectSuffix): herstelleredit.cpp $(IntermediateDirectory)/herstelleredit$(DependSuffix)
	@test -d ./Release || $(MakeDirCommand) ./Release
	$(CompilerName) $(SourceSwitch) "/media/3A64CC8964CC48F9/Projekte/Artikelverwaltung/Anwendung/herstelleredit.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/herstelleredit$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/herstelleredit$(DependSuffix): herstelleredit.cpp
	@test -d ./Release || $(MakeDirCommand) ./Release
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/herstelleredit$(ObjectSuffix) -MF$(IntermediateDirectory)/herstelleredit$(DependSuffix) -MM "/media/3A64CC8964CC48F9/Projekte/Artikelverwaltung/Anwendung/herstelleredit.cpp"

$(IntermediateDirectory)/lieferantadd$(ObjectSuffix): lieferantadd.cpp $(IntermediateDirectory)/lieferantadd$(DependSuffix)
	@test -d ./Release || $(MakeDirCommand) ./Release
	$(CompilerName) $(SourceSwitch) "/media/3A64CC8964CC48F9/Projekte/Artikelverwaltung/Anwendung/lieferantadd.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/lieferantadd$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/lieferantadd$(DependSuffix): lieferantadd.cpp
	@test -d ./Release || $(MakeDirCommand) ./Release
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/lieferantadd$(ObjectSuffix) -MF$(IntermediateDirectory)/lieferantadd$(DependSuffix) -MM "/media/3A64CC8964CC48F9/Projekte/Artikelverwaltung/Anwendung/lieferantadd.cpp"

$(IntermediateDirectory)/lieferantartikelconnect$(ObjectSuffix): lieferantartikelconnect.cpp $(IntermediateDirectory)/lieferantartikelconnect$(DependSuffix)
	@test -d ./Release || $(MakeDirCommand) ./Release
	$(CompilerName) $(SourceSwitch) "/media/3A64CC8964CC48F9/Projekte/Artikelverwaltung/Anwendung/lieferantartikelconnect.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/lieferantartikelconnect$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/lieferantartikelconnect$(DependSuffix): lieferantartikelconnect.cpp
	@test -d ./Release || $(MakeDirCommand) ./Release
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/lieferantartikelconnect$(ObjectSuffix) -MF$(IntermediateDirectory)/lieferantartikelconnect$(DependSuffix) -MM "/media/3A64CC8964CC48F9/Projekte/Artikelverwaltung/Anwendung/lieferantartikelconnect.cpp"

$(IntermediateDirectory)/lieferantedit$(ObjectSuffix): lieferantedit.cpp $(IntermediateDirectory)/lieferantedit$(DependSuffix)
	@test -d ./Release || $(MakeDirCommand) ./Release
	$(CompilerName) $(SourceSwitch) "/media/3A64CC8964CC48F9/Projekte/Artikelverwaltung/Anwendung/lieferantedit.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/lieferantedit$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/lieferantedit$(DependSuffix): lieferantedit.cpp
	@test -d ./Release || $(MakeDirCommand) ./Release
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/lieferantedit$(ObjectSuffix) -MF$(IntermediateDirectory)/lieferantedit$(DependSuffix) -MM "/media/3A64CC8964CC48F9/Projekte/Artikelverwaltung/Anwendung/lieferantedit.cpp"

$(IntermediateDirectory)/artikeladd$(ObjectSuffix): artikeladd.cpp $(IntermediateDirectory)/artikeladd$(DependSuffix)
	@test -d ./Release || $(MakeDirCommand) ./Release
	$(CompilerName) $(SourceSwitch) "/media/3A64CC8964CC48F9/Projekte/Artikelverwaltung/Anwendung/artikeladd.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/artikeladd$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/artikeladd$(DependSuffix): artikeladd.cpp
	@test -d ./Release || $(MakeDirCommand) ./Release
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/artikeladd$(ObjectSuffix) -MF$(IntermediateDirectory)/artikeladd$(DependSuffix) -MM "/media/3A64CC8964CC48F9/Projekte/Artikelverwaltung/Anwendung/artikeladd.cpp"

$(IntermediateDirectory)/artikeldetail$(ObjectSuffix): artikeldetail.cpp $(IntermediateDirectory)/artikeldetail$(DependSuffix)
	@test -d ./Release || $(MakeDirCommand) ./Release
	$(CompilerName) $(SourceSwitch) "/media/3A64CC8964CC48F9/Projekte/Artikelverwaltung/Anwendung/artikeldetail.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/artikeldetail$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/artikeldetail$(DependSuffix): artikeldetail.cpp
	@test -d ./Release || $(MakeDirCommand) ./Release
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/artikeldetail$(ObjectSuffix) -MF$(IntermediateDirectory)/artikeldetail$(DependSuffix) -MM "/media/3A64CC8964CC48F9/Projekte/Artikelverwaltung/Anwendung/artikeldetail.cpp"

$(IntermediateDirectory)/herstellerdetail$(ObjectSuffix): herstellerdetail.cpp $(IntermediateDirectory)/herstellerdetail$(DependSuffix)
	@test -d ./Release || $(MakeDirCommand) ./Release
	$(CompilerName) $(SourceSwitch) "/media/3A64CC8964CC48F9/Projekte/Artikelverwaltung/Anwendung/herstellerdetail.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/herstellerdetail$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/herstellerdetail$(DependSuffix): herstellerdetail.cpp
	@test -d ./Release || $(MakeDirCommand) ./Release
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/herstellerdetail$(ObjectSuffix) -MF$(IntermediateDirectory)/herstellerdetail$(DependSuffix) -MM "/media/3A64CC8964CC48F9/Projekte/Artikelverwaltung/Anwendung/herstellerdetail.cpp"

$(IntermediateDirectory)/lieferantdetail$(ObjectSuffix): lieferantdetail.cpp $(IntermediateDirectory)/lieferantdetail$(DependSuffix)
	@test -d ./Release || $(MakeDirCommand) ./Release
	$(CompilerName) $(SourceSwitch) "/media/3A64CC8964CC48F9/Projekte/Artikelverwaltung/Anwendung/lieferantdetail.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/lieferantdetail$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/lieferantdetail$(DependSuffix): lieferantdetail.cpp
	@test -d ./Release || $(MakeDirCommand) ./Release
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/lieferantdetail$(ObjectSuffix) -MF$(IntermediateDirectory)/lieferantdetail$(DependSuffix) -MM "/media/3A64CC8964CC48F9/Projekte/Artikelverwaltung/Anwendung/lieferantdetail.cpp"

$(IntermediateDirectory)/mainwindow$(ObjectSuffix): mainwindow.cpp $(IntermediateDirectory)/mainwindow$(DependSuffix)
	@test -d ./Release || $(MakeDirCommand) ./Release
	$(CompilerName) $(SourceSwitch) "/media/3A64CC8964CC48F9/Projekte/Artikelverwaltung/Anwendung/mainwindow.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/mainwindow$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/mainwindow$(DependSuffix): mainwindow.cpp
	@test -d ./Release || $(MakeDirCommand) ./Release
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/mainwindow$(ObjectSuffix) -MF$(IntermediateDirectory)/mainwindow$(DependSuffix) -MM "/media/3A64CC8964CC48F9/Projekte/Artikelverwaltung/Anwendung/mainwindow.cpp"

$(IntermediateDirectory)/configurationmanager$(ObjectSuffix): configurationmanager.cpp $(IntermediateDirectory)/configurationmanager$(DependSuffix)
	@test -d ./Release || $(MakeDirCommand) ./Release
	$(CompilerName) $(SourceSwitch) "/media/3A64CC8964CC48F9/Projekte/Artikelverwaltung/Anwendung/configurationmanager.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/configurationmanager$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/configurationmanager$(DependSuffix): configurationmanager.cpp
	@test -d ./Release || $(MakeDirCommand) ./Release
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/configurationmanager$(ObjectSuffix) -MF$(IntermediateDirectory)/configurationmanager$(DependSuffix) -MM "/media/3A64CC8964CC48F9/Projekte/Artikelverwaltung/Anwendung/configurationmanager.cpp"

$(IntermediateDirectory)/postgresql_connector$(ObjectSuffix): postgresql_connector.cpp $(IntermediateDirectory)/postgresql_connector$(DependSuffix)
	@test -d ./Release || $(MakeDirCommand) ./Release
	$(CompilerName) $(SourceSwitch) "/media/3A64CC8964CC48F9/Projekte/Artikelverwaltung/Anwendung/postgresql_connector.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/postgresql_connector$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/postgresql_connector$(DependSuffix): postgresql_connector.cpp
	@test -d ./Release || $(MakeDirCommand) ./Release
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/postgresql_connector$(ObjectSuffix) -MF$(IntermediateDirectory)/postgresql_connector$(DependSuffix) -MM "/media/3A64CC8964CC48F9/Projekte/Artikelverwaltung/Anwendung/postgresql_connector.cpp"

$(IntermediateDirectory)/dbcommand$(ObjectSuffix): dbcommand.cpp $(IntermediateDirectory)/dbcommand$(DependSuffix)
	@test -d ./Release || $(MakeDirCommand) ./Release
	$(CompilerName) $(SourceSwitch) "/media/3A64CC8964CC48F9/Projekte/Artikelverwaltung/Anwendung/dbcommand.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/dbcommand$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/dbcommand$(DependSuffix): dbcommand.cpp
	@test -d ./Release || $(MakeDirCommand) ./Release
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/dbcommand$(ObjectSuffix) -MF$(IntermediateDirectory)/dbcommand$(DependSuffix) -MM "/media/3A64CC8964CC48F9/Projekte/Artikelverwaltung/Anwendung/dbcommand.cpp"

$(IntermediateDirectory)/dbconnectionmanager$(ObjectSuffix): dbconnectionmanager.cpp $(IntermediateDirectory)/dbconnectionmanager$(DependSuffix)
	@test -d ./Release || $(MakeDirCommand) ./Release
	$(CompilerName) $(SourceSwitch) "/media/3A64CC8964CC48F9/Projekte/Artikelverwaltung/Anwendung/dbconnectionmanager.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/dbconnectionmanager$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/dbconnectionmanager$(DependSuffix): dbconnectionmanager.cpp
	@test -d ./Release || $(MakeDirCommand) ./Release
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/dbconnectionmanager$(ObjectSuffix) -MF$(IntermediateDirectory)/dbconnectionmanager$(DependSuffix) -MM "/media/3A64CC8964CC48F9/Projekte/Artikelverwaltung/Anwendung/dbconnectionmanager.cpp"

$(IntermediateDirectory)/pq_multithread_wrapper$(ObjectSuffix): pq_multithread_wrapper.cpp $(IntermediateDirectory)/pq_multithread_wrapper$(DependSuffix)
	@test -d ./Release || $(MakeDirCommand) ./Release
	$(CompilerName) $(SourceSwitch) "/media/3A64CC8964CC48F9/Projekte/Artikelverwaltung/Anwendung/pq_multithread_wrapper.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/pq_multithread_wrapper$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/pq_multithread_wrapper$(DependSuffix): pq_multithread_wrapper.cpp
	@test -d ./Release || $(MakeDirCommand) ./Release
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/pq_multithread_wrapper$(ObjectSuffix) -MF$(IntermediateDirectory)/pq_multithread_wrapper$(DependSuffix) -MM "/media/3A64CC8964CC48F9/Projekte/Artikelverwaltung/Anwendung/pq_multithread_wrapper.cpp"

$(IntermediateDirectory)/updatedaemon$(ObjectSuffix): updatedaemon.cpp $(IntermediateDirectory)/updatedaemon$(DependSuffix)
	@test -d ./Release || $(MakeDirCommand) ./Release
	$(CompilerName) $(SourceSwitch) "/media/3A64CC8964CC48F9/Projekte/Artikelverwaltung/Anwendung/updatedaemon.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/updatedaemon$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/updatedaemon$(DependSuffix): updatedaemon.cpp
	@test -d ./Release || $(MakeDirCommand) ./Release
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/updatedaemon$(ObjectSuffix) -MF$(IntermediateDirectory)/updatedaemon$(DependSuffix) -MM "/media/3A64CC8964CC48F9/Projekte/Artikelverwaltung/Anwendung/updatedaemon.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/main$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/main$(DependSuffix)
	$(RM) $(IntermediateDirectory)/main$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/artikelpanel$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/artikelpanel$(DependSuffix)
	$(RM) $(IntermediateDirectory)/artikelpanel$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/herstellerpanel$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/herstellerpanel$(DependSuffix)
	$(RM) $(IntermediateDirectory)/herstellerpanel$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/lieferantpanel$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/lieferantpanel$(DependSuffix)
	$(RM) $(IntermediateDirectory)/lieferantpanel$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/settingspanel$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/settingspanel$(DependSuffix)
	$(RM) $(IntermediateDirectory)/settingspanel$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/artikeledit$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/artikeledit$(DependSuffix)
	$(RM) $(IntermediateDirectory)/artikeledit$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/artikellieferantconnect$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/artikellieferantconnect$(DependSuffix)
	$(RM) $(IntermediateDirectory)/artikellieferantconnect$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/herstelleradd$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/herstelleradd$(DependSuffix)
	$(RM) $(IntermediateDirectory)/herstelleradd$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/herstelleredit$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/herstelleredit$(DependSuffix)
	$(RM) $(IntermediateDirectory)/herstelleredit$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/lieferantadd$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/lieferantadd$(DependSuffix)
	$(RM) $(IntermediateDirectory)/lieferantadd$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/lieferantartikelconnect$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/lieferantartikelconnect$(DependSuffix)
	$(RM) $(IntermediateDirectory)/lieferantartikelconnect$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/lieferantedit$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/lieferantedit$(DependSuffix)
	$(RM) $(IntermediateDirectory)/lieferantedit$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/artikeladd$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/artikeladd$(DependSuffix)
	$(RM) $(IntermediateDirectory)/artikeladd$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/artikeldetail$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/artikeldetail$(DependSuffix)
	$(RM) $(IntermediateDirectory)/artikeldetail$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/herstellerdetail$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/herstellerdetail$(DependSuffix)
	$(RM) $(IntermediateDirectory)/herstellerdetail$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/lieferantdetail$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/lieferantdetail$(DependSuffix)
	$(RM) $(IntermediateDirectory)/lieferantdetail$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/mainwindow$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/mainwindow$(DependSuffix)
	$(RM) $(IntermediateDirectory)/mainwindow$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/configurationmanager$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/configurationmanager$(DependSuffix)
	$(RM) $(IntermediateDirectory)/configurationmanager$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/postgresql_connector$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/postgresql_connector$(DependSuffix)
	$(RM) $(IntermediateDirectory)/postgresql_connector$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/dbcommand$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/dbcommand$(DependSuffix)
	$(RM) $(IntermediateDirectory)/dbcommand$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/dbconnectionmanager$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/dbconnectionmanager$(DependSuffix)
	$(RM) $(IntermediateDirectory)/dbconnectionmanager$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/pq_multithread_wrapper$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/pq_multithread_wrapper$(DependSuffix)
	$(RM) $(IntermediateDirectory)/pq_multithread_wrapper$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/updatedaemon$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/updatedaemon$(DependSuffix)
	$(RM) $(IntermediateDirectory)/updatedaemon$(PreprocessSuffix)
	$(RM) $(OutputFile)


