#include <iostream>
#include <string>
#include <fstream>
#include <stddef.h>
#include <time.h>

typedef enum e_options
{
	O_MONTH,
	O_WEEK,
	O_DAYS,
	O_EXAMS,
	O_MATERIA,
	O_OTHER
}	e_options;

typedef enum e_data
{
	D_MONTH,
	D_WEEK,
	D_DAY,
	D_MATERIA,
	D_OTHER
}	e_data;

const int	g_max_materia = 11;
const int	g_max_month = 12;

static const std::string	months[12] = {
	"JANVIER", "FEVRIER", "MARS", "AVRIL", "MAI", "JUIN", "JUILLET",
	"AOUT", "SEPTEMBRE", "OCTOBRE", "NOVEMBRE", "DECEMBRE"
};

static const std::string	materias[11] = {
	"MATH", "PHYSIQUE", "MATERIAU", "CHIMIE", "MICROTECH",
	"ELECTRONIQUE", "MOTEURS", "EDC", "SIGNAUX", "C", "CAO"
};

static const std::string	pseudos[11] = {
	"MATH", "PHY", "MATE", "CHI", "MIC", "ELE", "MOT", "EDC", "SIG", "C", "CAO"
};

std::string	getContent(std::string file)
{
	std::string	buf = "";
	std::string	line = "";
	std::ifstream	stream(file);

	if (!stream.is_open())
		return "";
	while (std::getline(stream, line))
	{
		buf.append(line);
		buf.append("\n");
	}
	return buf;
}

int	propose()
{
	std::cout << "Chose :\n"
		<< O_MONTH << ": Acutal month\n"
		<< O_WEEK << ": Actual week\n"
		<< O_DAYS << ": what happens these Days\n"
		<< O_EXAMS << ": Exams\n"
		<< O_MATERIA << ": Materia\n"
		<< "5: Other\n"
		<< std::endl;
	std::cout << '\n';
	std::string response = "";
	std::getline(std::cin, response);
	if (response.empty())
		return -1;
	return atoi(response.c_str());
}

std::string	month(std::string content, std::string m = "OCTOBRE")
{
	size_t	begin = content.find(m);
	size_t	end = 0;
	std::string	next = "";

	for (int i = 0; i < 12; i++)
	{
		if (months[i] == m)
		{
			if (i == 11)
				next = "JANVIER";
			else
				next = months[i + 1];
			break ;
		}
	}
	end = content.find(next);

	std::cout << m;
	if (end == std::string::npos || begin == std::string::npos) {
		std::cout << "Data not found\n"; return ""; }
	std::string foo = content.substr(begin, end - begin);
	return foo;
}

std::string	week(std::string content, std::string w = "now")
{

	return ""; (void)content; (void)w;
}

std::string	materia(std::string content, std::string m = "all")
{

	return ""; (void)content; (void)m;
}

std::string	exams(std::string content)
{
	return ""; (void)content;
}

void	display(int option, std::string search = "", std::string time = "")
{
	std::string	content = getContent("agenda.txt");

	std::cout << "Displaying information\n" << std::flush;
	switch (option)
	{
		case O_MONTH:
			std::cout << "Display month info\n";	
			if (!search.empty())
			{
				std::cout << month(content, search) << std::endl;
			}
			else
				std::cout << month(content);
			break ;
		case O_WEEK:
			if (!search.empty())
			{
				std::cout << week(content, search) << std::endl;
			}
			std::cout << "Display week info\n";
			break ;
		case 1000:
			std::cout << "Display now info\n";
			break ;
		case O_EXAMS:
			std::cout << "Display exams\n";
			std::cout << exams(content) << std::endl;
			break ;
		case O_MATERIA:
			if (!search.empty())
			{
				std::cout << materia(content, search) << std::endl;
			}
			std::cout << "Display materia info\n";
			break ;
		default:
			std::cout << "Request not valid\n" << "Display default\n";
			display(O_MONTH, "", time);
			break ;
	}
}

int	id(char *what)
{
	(void)what;
	return (0);
}

int	filter(std::string f, std::string input)
{
	(void)f;
//	int	flag = id(f.c_str());
//
//	(void)flag;
	// switch (flag)
	// {
		// case 0:
			// break;
		// default:
			// break;
	// }
// 
	std::cout << "Filtering input\n" << std::flush;
	for (int i = 0; i < g_max_materia; i++)
	{
		if (input == materias[i])
			return display(O_MATERIA, input),1;
	}
	for (int i = 0; i < g_max_month; i++)
	{
		if (input == months[i])
			return display(O_MONTH, input),1;
	}
	return 1;
}

int	main(int ac, char **av)
{

	switch (ac)
	{
		case 0:
			break ;
		case 2:
			filter(std::string(av[1]), std::string(""));
			break ;
		case 3:
			filter(std::string(av[1]), std::string(av[2]));
			break ;
		default:
			break ;
	}
	struct tm* ptr;
    // Variable to store current time
    time_t t;
    // Get current time
    t = time(NULL);
    // Convert it to local time
    ptr = localtime(&t);

	std::cout << asctime(ptr) << std::endl;

	int	option = propose();

	display(option, "", std::string(asctime(ptr)));
	return 0;
}
