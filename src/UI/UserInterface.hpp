/*
 * UserInterface.hpp
 *
 *  Created on: 7 Jan 2017
 *      Author: David
 */

#ifndef SRC_UI_USERINTERFACE_HPP_
#define SRC_UI_USERINTERFACE_HPP_

#include "FirmwareFeatures.hpp"
#include <ObjectModel/BedOrChamber.hpp>
#include <ObjectModel/PrinterStatus.hpp>
#include <ObjectModel/Spindle.hpp>
#include <ObjectModel/Tool.hpp>
#include <UI/ColourSchemes.hpp>
#include <UI/Display.hpp>
#include <UI/Events.hpp>
#include <General/String.h>
#include <General/StringFunctions.h>

extern MainWindow mgr;
extern IntegerField *freeMem;
extern StaticTextField *debugField;
extern StaticTextField *touchCalibInstruction;
extern StaticTextField *messageTextFields[], *messageTimeFields[];
extern TextField *fwVersionField;

const size_t alertTextLength = 165;			// maximum characters in the alert text
const size_t alertTitleLength = 50;			// maximum characters in the alert title

class Alert
{
private:
public:
	int32_t mode;
	uint32_t seq;
	uint32_t controls;
	float timeout;
	Bitmap<uint8_t> flags;
	String<50> title;
	String<alertTextLength> text;

	static constexpr uint8_t GotMode = 0;
	static constexpr uint8_t GotSeq = 1;
	static constexpr uint8_t GotTimeout = 2;
	static constexpr uint8_t GotTitle = 3;
	static constexpr uint8_t GotText = 4;
	static constexpr uint8_t GotControls = 5;
	static constexpr uint8_t GotAll =
			(1 << GotMode)
			| (1 << GotSeq)
			| (1 << GotTimeout)
			| (1 << GotTitle)
			| (1 << GotText)
			| (1 << GotControls);

	Alert() : mode(0), seq(0), controls(0), timeout(0.0) { flags.Clear(); }

	bool AllFlagsSet() const { return flags.GetRaw() == GotAll; }
};


namespace UI
{
	extern unsigned int GetNumLanguages();
	extern void CreateFields(uint32_t language, const ColourScheme& colours, uint32_t p_infoTimeout);
	extern void InitColourScheme(const ColourScheme *scheme);
	extern void ActivateScreensaver();
	extern bool DeactivateScreensaver();
	extern void AnimateScreensaver();
	extern void ShowAxis(size_t axis, bool b, const char* axisLetter = nullptr);
	extern void UpdateAxisPosition(size_t axis, float fval);
	extern void UpdateCurrentTemperature(size_t heater, float fval);
	extern void UpdateHeaterStatus(const size_t heater, const OM::HeaterStatus status);
	extern void ChangeStatus(OM::PrinterStatus oldStatus, OM::PrinterStatus newStatus);
	extern void UpdateTimesLeft(size_t index, unsigned int seconds);
	extern void UpdateDuration(uint32_t duration);
	extern void UpdateWarmupDuration(uint32_t warmupDuration);
	extern void SetSimulatedTime(uint32_t simulatedTime);
	extern bool ChangePage(ButtonBase *newTab);
	extern bool DoPolling();
	extern void Tick();
	extern void Spin();
	extern void PrintStarted();
	extern void PrintingFilenameChanged(const char data[]);
	extern void LastJobFileNameAvailable(const bool available);
	extern void SetLastFileSimulated(const bool lastFileSimulated);
	extern void ShowDefaultPage();
	extern void UpdatePrintingFields();
	extern void SetPrintProgressPercent(unsigned int percent);
	extern void UpdateGeometry(unsigned int p_numAxes, bool p_isDelta);
	extern void UpdateHomedStatus(size_t axis, bool isHomed);
	extern void UpdateZProbe(const char data[]);
	extern void UpdateMachineName(const char data[]);
	extern void UpdateIP(const char data[]);
	extern void ProcessAlert(const Alert& alert);
	extern void ClearAlert();
	extern void ProcessSimpleAlert(const char* _ecv_array text);
	extern void NewResponseReceived(const char* _ecv_array text);
	extern bool CanDimDisplay();
	extern void UpdateFileLastModifiedText(const char data[]);
	extern void UpdateFileGeneratedByText(const char data[]);
	extern void UpdateFileObjectHeight(float f);
	extern void UpdateFileLayerHeight(float f);
	extern void UpdateFileSize(int size);
	extern void UpdateFileFilament(int len);
	extern void UpdateFanPercent(size_t fanIndex, int rpm);
	extern void UpdateActiveTemperature(size_t index, int ival);
	extern void UpdateToolTemp(size_t toolIndex, size_t toolHeaterIndex, int32_t temp, bool active);
	extern void UpdateStandbyTemperature(size_t index, int ival);
	extern void UpdateExtrusionFactor(size_t index, int ival);
	extern void UpdatePrintTimeText(uint32_t seconds, bool isSimulated);
	extern void UpdateSpeedPercent(int ival);
	extern void ProcessTouch(ButtonPress bp);
	extern void ProcessTouchOutsidePopup(ButtonPress bp)
	pre(bp.IsValid());
	extern void OnButtonPressTimeout();
	extern bool IsDisplayingFileInfo();
	extern void AllToolsSeen();

	extern void DisplayFilesOrMacrosList(bool filesNotMacros, int cardNumber, unsigned int numVolumes);
	extern void FileListLoaded(bool filesNotMacros, int errCode);
	extern void EnableFileNavButtons(bool filesNotMacros, bool scrollEarlier, bool scrollLater, bool parentDir);
	extern void UpdateFileButton(bool filesNotMacros, unsigned int buttonIndex, const char * _ecv_array null text, const char * _ecv_array null param);
	extern unsigned int GetNumScrolledFiles(bool filesNotMacros);
	extern bool UpdateMacroShortList(unsigned int buttonIndex, const char * _ecv_array null fileName);

	extern void SetBabystepOffset(size_t index, float f);
	extern void SetAxisLetter(size_t index, char l);
	extern void SetAxisVisible(size_t index, bool v);
	extern void SetAxisWorkplaceOffset(size_t axisIndex, size_t workplaceIndex, float offset);
	extern void SetCurrentWorkplaceNumber(uint8_t workplaceNumber);

	extern void SetCurrentTool(int32_t tool);
	extern void UpdateToolStatus(size_t index, OM::ToolStatus status);
	extern void SetToolExtruder(size_t toolIndex, uint8_t extruder);
	extern void SetToolFan(size_t toolIndex, uint8_t fan);
	extern void SetToolHeater(size_t toolIndex, uint8_t toolHeaterIndex, uint8_t heaterIndex);
	extern void SetToolSpindle(int8_t toolIndex, int8_t spindleNumber);
	extern bool RemoveToolHeaters(const size_t toolIndex, const uint8_t firstIndexToDelete);
	extern void SetToolOffset(size_t toolIndex, size_t axisIndex, float offset);

	extern void SetBedOrChamberHeater(const uint8_t heaterIndex, const int8_t heaterNumber, bool bed = true);

	extern void SetSpindleActive(size_t spindleIndex, int32_t activeRpm);
	extern void SetSpindleCurrent(size_t spindleIndex, int32_t currentRpm);
	extern void SetSpindleLimit(size_t spindleIndex, uint32_t value, bool max);
	extern void SetSpindleState(size_t spindleIndex, OM::SpindleState state);
	extern void SetSpindleTool(int8_t spindleNumber, int8_t toolIndex);
}

#endif /* SRC_UI_USERINTERFACE_HPP_ */
