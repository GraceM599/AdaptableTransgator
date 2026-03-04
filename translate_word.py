import nltk
from nltk.corpus import wordnet as wn
from nltk.stem import WordNetLemmatizer
#Spanish for now but we can work on the other ones later

#Run once only but it needs to be run once
#nltk.download("wordnet")
#nltk.download("omw-1.4")

#https://www.nltk.org/api/nltk.stem.wordnet.html
lemmatizer = WordNetLemmatizer()

def translate_word(word, top_n=3):
    """
    Translate a word into Spanish
    Interprets the part of speech, filters out first lemma for animals/plants,
    and uses a pretty useless back-translation.
    Returns the top Spanish translation (for now)
    """
    # get all base forms of a word by part of speech (pos)
    bases = {}
    for pos in ['n', 'v', 'a', 'r']:
        lemma = lemmatizer.lemmatize(word, pos=pos)
        synsets = wn.synsets(lemma, pos=pos)
        if synsets:
            bases[pos] = synsets

    if not bases:
        return None  # no synsets found

    #store all the possible translations
    candidates = []
    for pos, synsets in bases.items():
        #takes the top_n number of pos's, not too important for now
        for syn in synsets[:top_n]:
            lemmas = syn.lemma_names('spa')
            #it apparently can see what category a word is in and the first lemma of
            #an animal/plant is usually the genus name which messes things up.
            if syn.lexname() in ["noun.animal", "noun.plant"]:
                lemmas = lemmas[1:]  # skip first lemma (genus/scientific name if its an animal or plant)
            for lemma in lemmas:
                if lemma not in candidates:
                    candidates.append(lemma)

    if not candidates:
        return None

    #back translation (doesn't work I was trying to fix the genus name issue)
    #it tries to remove weird translations by running it through the translator twice and seeing if it matches
    for spa in candidates:
        eng_back = []
        for syn in wn.synsets(spa, lang='spa'):
            for l in syn.lemma_names('eng'):
                eng_back.append(l.lower())
        if word.lower() in eng_back:
            return spa  # top translation

    return candidates[0]

print(translate_word("cat"))