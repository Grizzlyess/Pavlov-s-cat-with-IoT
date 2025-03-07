import requests #interagir com o ESP8266, enviando comandos via HTTP
from telegram import Update # interagir com a API do Telegram
from telegram.ext import Application, CommandHandler, MessageHandler, filters, ContextTypes #tratar as interações dos usuários com o bot

TOKEN = "UmMonteDeLetrasENumeros" # Substituir seu token do telegram
ESP8266_IP = "....."  # Substituir pelo IP do terminal do arduino

#chamada sempre que o bot receber uma mensagem
async def handle_message(update: Update, context: ContextTypes.DEFAULT_TYPE) -> None:  
    user_message = update.message.text  

    if user_message == "Tocar Música Certa": 
        response = requests.get(f"{ESP8266_IP}/tocar_musica_certa")
        await update.message.reply_text(f"🎵 {response.text}")
        print("TOCAR MUSICA CERTA")

    elif user_message == "Tocar Música Errada":
        response = requests.get(f"{ESP8266_IP}/tocar_musica_errada")
        await update.message.reply_text(f"🚫 {response.text}")
        print("TOCAR MUSICA ERRADA")

    else:
        await update.message.reply_text("Olá!!! Eu sou o Pavlov, seu treinador de pets. Escolha uma opção no teclado:")
        print("COMECOU")

def main():
    app = Application.builder().token(TOKEN).build()

    # Adiciona um comando /start
    app.add_handler(CommandHandler("start", handle_message))
    
    # Adiciona um handler para qualquer mensagem recebida
    app.add_handler(MessageHandler(filters.TEXT & ~filters.COMMAND, handle_message))

    print("Bot rodando...")
    app.run_polling()

if __name__ == "__main__":
    main()
