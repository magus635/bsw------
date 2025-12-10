
import os
import re
import sys
import json
import json
import math

# Try to import google.generativeai
try:
    import google.generativeai as genai
except ImportError:
    print("Error: google-generativeai not installed. Please run: pip install google-generativeai")
    sys.exit(1)

# Optional numpy
try:
    import numpy as np
    HAS_NUMPY = True
except ImportError:
    HAS_NUMPY = False

# Configuration
API_KEY = os.environ.get("GEMINI_API_KEY")
DATASET_PATH = "datasheets/sample_chip_manual.txt"
EMBEDDING_MODEL = "models/embedding-001"
GENERATION_MODEL = "gemini-pro"

def load_api_key():
    """Load API Key from env or ask user"""
    global API_KEY, GENERATION_MODEL
    
    # Try loading from app settings if available (mocking this lookup based on project structure)
    # in real app, we might look at QSettings or a json file.
    # For this prototype, we rely on ENV or input.
    
    if not API_KEY:
        print("⚠️ GEMINI_API_KEY not found in environment variables.")
        try:
            # check local config if exists
            with open("config.json", "r") as f:
                data = json.load(f)
                API_KEY = data.get("api_key")
        except:
            pass
            
    if not API_KEY:
        API_KEY = input("Please enter your Gemini API Key: ").strip()
        
    if not API_KEY:
        print("❌ API Key is required.")
        sys.exit(1)
        
    genai.configure(api_key=API_KEY)
    
    # Check for available models to confirm connection and pick generation model
    try:
        models = [m.name for m in genai.list_models() if 'generateContent' in m.supported_generation_methods]
        
        preferred = ['models/gemini-1.5-flash', 'models/gemini-pro']
        for p in preferred:
            if p in models:
                GENERATION_MODEL = p
                print(f"✅ Connected. Using model: {GENERATION_MODEL}")
                break
    except Exception as e:
        print(f"❌ Failed to connect to Gemini: {e}")
        sys.exit(1)

class SimpleVectorDB:
    def __init__(self):
        self.documents = [] # List of strings
        self.embeddings = [] # List of vectors
        
    def add_document(self, text: str):
        """Add text, calculate embedding, store."""
        print(f"   Indexing chunk: {text[:40]}...")
        try:
            result = genai.embed_content(
                model=EMBEDDING_MODEL,
                content=text,
                task_type="retrieval_document"
            )
            embedding = result['embedding']
            self.documents.append(text)
            self.embeddings.append(embedding)
        except Exception as e:
            print(f"   ❌ Failed to embed chunk: {e}")

    def search(self, query: str, top_k: int = 3):
        """Search for relevant documents."""
        print(f"\n🔍 Searching for: '{query}'")
        try:
            result = genai.embed_content(
                model=EMBEDDING_MODEL,
                content=query,
                task_type="retrieval_query"
            )
            query_embedding = result['embedding']
            
            # Calculate Cosine Similarity
            scores = []
            if HAS_NUMPY:
                q_vec = np.array(query_embedding)
                q_norm = np.linalg.norm(q_vec)
                
                for doc_emb in self.embeddings:
                    d_vec = np.array(doc_emb)
                    similarity = np.dot(q_vec, d_vec) / (q_norm * np.linalg.norm(d_vec))
                    scores.append(similarity)
            else:
                # Pure Python implementation
                def dot_product(v1, v2):
                    return sum(x * y for x, y in zip(v1, v2))
                
                def magnitude(v):
                    return math.sqrt(sum(x * x for x in v))
                    
                q_mag = magnitude(query_embedding)
                
                for doc_emb in self.embeddings:
                    d_mag = magnitude(doc_emb)
                    if q_mag * d_mag == 0:
                        similarity = 0
                    else:
                        similarity = dot_product(query_embedding, doc_emb) / (q_mag * d_mag)
                    scores.append(similarity)
                
                # Get indices of top K
                # (Simple sort with index)
                indexed_scores = list(enumerate(scores))
                indexed_scores.sort(key=lambda x: x[1], reverse=True)
                top_indices = [x[0] for x in indexed_scores[:top_k]]
            
            results = []
            # Reset top_indices if numpy was used (it returns numpy array of indices)
            if HAS_NUMPY:
                top_indices = np.argsort(scores)[::-1][:top_k]

            for idx in top_indices:
                if scores[idx] > 0.3: # Threshold
                    results.append((self.documents[idx], scores[idx]))
            
            return results
            
        except Exception as e:
            print(f"   ❌ Search failed: {e}")
            return []

def chunk_text(text: str):
    """Simple chunking by sections"""
    chunks = []
    current_chunk = []
    
    lines = text.split('\n')
    for line in lines:
        if line.startswith('## '):
            if current_chunk:
                chunks.append("\n".join(current_chunk))
            current_chunk = [line]
        else:
            current_chunk.append(line)
            
    if current_chunk:
        chunks.append("\n".join(current_chunk))
    return chunks

def main():
    load_api_key()
    
    # 1. Ingest Knowledge
    print(f"\n📚 Loading knowledge from {DATASET_PATH}...")
    if not os.path.exists(DATASET_PATH):
        print(f"❌ File {DATASET_PATH} not found.")
        return

    with open(DATASET_PATH, 'r') as f:
        content = f.read()
        
    chunks = chunk_text(content)
    print(f"   Found {len(chunks)} knowledge chunks.")
    
    db = SimpleVectorDB()
    for chunk in chunks:
        db.add_document(chunk)
        
    print("✅ Knowledge Base built successfully!")
    
    # 2. Interactive Loop
    model = genai.GenerativeModel(GENERATION_MODEL)
    
    print("\n🤖 AI Assistant with Knowledge Base Ready! (Type 'exit' to quit)")
    print("Test Queries: 'What is max baudrate?', 'How to handle SPI error?'")
    
    while True:
        query = input("\nYou: ").strip()
        if query.lower() in ['exit', 'quit']:
            break
        if not query:
            continue
            
        # Retrieval
        relevant_docs = db.search(query)
        
        context_str = ""
        if relevant_docs:
            print(f"   Found {len(relevant_docs)} relevant context(s):")
            for i, (doc, score) in enumerate(relevant_docs):
                print(f"   [{i+1}] (Score: {score:.2f}) {doc.splitlines()[0]}")
                context_str += f"\n--- Context {i+1} ---\n{doc}\n"
        else:
            print("   No specific relevant context found in manual.")
        
        # Generation
        prompt = f"""
        You are an expert embedded software engineer. 
        Answer the user's question based strictly on the provided Context below.
        If the answer is not in the context, say "I don't find that in the manual."
        
        Context:
        {context_str}
        
        User Question: {query}
        """
        
        print("   🧠 Thinking...")
        try:
            response = model.generate_content(prompt)
            print(f"\nAI: {response.text}")
        except Exception as e:
            print(f"❌ Generation failed: {e}")

if __name__ == "__main__":
    main()
