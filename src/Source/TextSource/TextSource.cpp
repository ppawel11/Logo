#include <QStringBuilder>
#include "TextSource.h"

char TextSource::getNextChar() {
    char next_char = code_stream.get()->get();

    // todo: obsługa wszystkich sekwencji znaków nowej linii CRLF
    if( next_char == '\n' )
    {
        current_position.sign = 0;
        while( next_char == '\n' )
        {
            current_position.line++;
            next_char = code_stream.get()->get();
        }
    }

    current_position.sign++;

    current_char = next_char;
    current_position.stream_position = code_stream.get()->tellg();
    return next_char;
}

char TextSource::peek() {
    return static_cast<char>( code_stream.get()->peek() );
}

bool TextSource::eof() {
    return code_stream.get()->eof();
}

void TextSource::set_code(const QString& code_) {
    code = code_;
    code_stream = std::make_unique<std::istringstream>(code_.toStdString());

    current_char = 0;
    current_position.sign = 0;
    current_position.line = 0;
    current_position.stream_position = 0;

    emit code_changed();
}

QString TextSource::get_code() {
    return code;
}
