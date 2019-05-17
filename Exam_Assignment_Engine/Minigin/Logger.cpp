#include "MiniginPCH.h"
#include "Logger.h"
#include <thread>

dae::Logger::Logger()
{
	m_logInfo = true;
	AutoScroll = true;
	ScrollToBottom = false;
	m_Open = true;
	Clear();
}

dae::Logger::~Logger()
{

}
void dae::Logger::AddLog(const char* fmt, ...) IM_FMTARGS(2)
{
	int old_size = Buf.size();
	va_list args;
	va_start(args, fmt);
	Buf.appendfv(fmt, args);
	va_end(args);
	for (int new_size = Buf.size(); old_size < new_size; old_size++)
		if (Buf[old_size] == '\n')
			LineOffsets.push_back(old_size + 1);
	if (AutoScroll)
		ScrollToBottom = true;
}

void dae::Logger::LogWarning(const std::wstring& message)
{
	std::string str{ message.begin(), message.end() };
	m_CurrColor = { 1,1,0,1 };
	AddLog("[%.1f][WARNING] '%s'\n", ImGui::GetTime(), str.c_str());
}

void dae::Logger::LogError(const std::wstring& message)
{
	std::string str{ message.begin(), message.end() };
	m_CurrColor = { 1,0,0,1 };
	AddLog("[%.1f][ERROR] '%s'\n", ImGui::GetTime(), str.c_str());
}

void dae::Logger::LogInfo(const std::wstring& message)
{
	std::string str{ message.begin(), message.end() };
	if (m_logInfo)
	{
		m_CurrColor = { 1,1,1,1 };
		AddLog("[%.1f][INFO] '%s'\n", ImGui::GetTime(), str.c_str());
	}
}

void dae::Logger::EnableInfoLogging()
{
	m_logInfo = true;
}

void dae::Logger::DisableInfoLogging()
{
	m_logInfo = false;
}

void dae::Logger::Draw()
{
	if (!m_Open) return;

	ImGui::SetNextWindowSize(ImVec2(360, 240), ImGuiCond_FirstUseEver);
	if (!ImGui::Begin("LOGGER", &m_Open, ImGuiWindowFlags_NoNavInputs))
	{
		ImGui::End();
		return;
	}

	// Options menu
	if (ImGui::Checkbox("Auto-scroll", &AutoScroll))
		if (AutoScroll)
			ScrollToBottom = true;
	ImGui::SameLine();

	// Main window
	bool clear = ImGui::Button("Clear");
	ImGui::SameLine();
	bool copy = ImGui::Button("Copy");
	ImGui::SameLine();
	Filter.Draw("Filter", -100.0f);

	ImGui::Separator();
	ImGui::BeginChild("scrolling", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);

	if (clear)
		Clear();
	if (copy)
		ImGui::LogToClipboard();

	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
	const char* buf = Buf.begin();
	const char* buf_end = Buf.end();
	if (Filter.IsActive())
	{
		for (int line_no = 0; line_no < LineOffsets.Size; line_no++)
		{
			const char* line_start = buf + LineOffsets[line_no];
			const char* line_end = (line_no + 1 < LineOffsets.Size) ? (buf + LineOffsets[line_no + 1] - 1) : buf_end;
			if (Filter.PassFilter(line_start, line_end))
				ImGui::TextUnformatted(line_start, line_end);
		}
	}
	else
	{
		ImGuiListClipper clipper;
		clipper.Begin(LineOffsets.Size);
		while (clipper.Step())
		{
			for (int line_no = clipper.DisplayStart; line_no < clipper.DisplayEnd; line_no++)
			{
				const char* line_start = buf + LineOffsets[line_no];
				const char* line_end = (line_no + 1 < LineOffsets.Size) ? (buf + LineOffsets[line_no + 1] - 1) : buf_end;
				ImGui::TextUnformatted(line_start, line_end);
			}
		}
		clipper.End();
	}
	ImGui::PopStyleVar();

	if (ScrollToBottom)
		ImGui::SetScrollHereY(1.0f);
	ScrollToBottom = false;
	ImGui::EndChild();
	ImGui::End();
}

void dae::Logger::Clear()
{
	Buf.clear();
	LineOffsets.clear();
	LineOffsets.push_back(0);
}
