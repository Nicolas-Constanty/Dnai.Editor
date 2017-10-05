#ifndef ICOMMAND_H
#define ICOMMAND_H

class ICommand
{
public:
	virtual ~ICommand() = default;
	
	/**
	 * \brief Execute the command
	 */
	virtual void execute() const = 0;
	
	/**
     * \brief Reverse the command
     */
    virtual void unExcute() const = 0;
};

#endif // ICOMMAND_H
