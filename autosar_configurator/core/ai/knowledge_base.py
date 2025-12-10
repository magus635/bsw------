"""
Knowledge Base Module for RAG (Retrieval-Augmented Generation)
"""
import os
import json
import math
from typing import List, Tuple, Optional

try:
    import google.generativeai as genai
    HAS_GEMINI = True
except ImportError:
    HAS_GEMINI = False

# Optional numpy
try:
    import numpy as np
    HAS_NUMPY = True
except ImportError:
    HAS_NUMPY = False

# Optional pypdf
try:
    import pypdf
    HAS_PYPDF = True
except ImportError:
    HAS_PYPDF = False

# Optional Pillow
try:
    from PIL import Image
    HAS_PILLOW = True
except ImportError:
    HAS_PILLOW = False

class KnowledgeBase:
    """
    Manages knowledge ingestion, embedding, and retrieval.
    """
    
    EMBEDDING_MODEL = "models/embedding-001"
    
    def __init__(self, api_key: Optional[str] = None):
        self.documents: List[str] = []
        self.embeddings: List[List[float]] = []
        self.is_ready = False
        
        if api_key and HAS_GEMINI:
            try:
                genai.configure(api_key=api_key)
                self.is_ready = True
            except Exception as e:
                print(f"Error configuring KnowledgeBase: {e}")

    def load_document(self, file_path: str):
        """
        Load and ingest a document (Text, PDF, or Image).
        """
        if not os.path.exists(file_path):
            print(f"Error: File not found: {file_path}")
            return
            
        print(f"Loading document: {file_path}")
        try:
            _, ext = os.path.splitext(file_path)
            content = ""
            ext_lower = ext.lower()
            
            if ext_lower == '.pdf':
                if not HAS_PYPDF:
                    print("Error: pypdf not installed. Cannot read PDF.")
                    return
                
                with open(file_path, 'rb') as f:
                    pdf_reader = pypdf.PdfReader(f)
                    text_parts = []
                    for page in pdf_reader.pages:
                        extracted = page.extract_text()
                        if extracted:
                            text_parts.append(extracted)
                    content = "\n".join(text_parts)
                    
            elif ext_lower in ['.jpg', '.jpeg', '.png']:
                if not HAS_PILLOW:
                    print("Error: Pillow not installed. Cannot read images.")
                    return
                self.ingest_image(file_path)
                return # ingest_image handles ingestion directly
                
            else:
                # Default to text
                with open(file_path, 'r', encoding='utf-8') as f:
                    content = f.read()
            
            if content:
                # Add source info to content
                filename = os.path.basename(file_path)
                tagged_content = f"Source Document: {filename}\n\n{content}"
                self.ingest_text(tagged_content)
                print(f"Successfully ingested: {filename}")
            else:
                print("Warning: Document was empty.")
                
        except Exception as e:
            print(f"Error loading document {file_path}: {e}")

    def ingest_image(self, image_path: str):
        """
        Ingest image content using Gemini Vision.
        """
        if not self.is_ready:
            print("KnowledgeBase not ready.")
            return

        print(f"Transcribing image: {image_path}...")
        try:
            img = Image.open(image_path)
            model = genai.GenerativeModel('gemini-1.5-flash')
            
            prompt = (
                "Transcribe the text in this image verbatim. "
                "If there are tables, verify they are formatted as Markdown tables. "
                "Do not summarize, just extract text present in the image."
            )
            
            response = model.generate_content([prompt, img])
            text = response.text
            
            if text:
                filename = os.path.basename(image_path)
                tagged_content = f"Source Image: {filename}\n\n{text}"
                self.ingest_text(tagged_content)
                print(f"Successfully transcribed and ingested: {filename}")
            else:
                print("Warning: No text transcribed from image.")
                
        except Exception as e:
            print(f"Error ingesting image {image_path}: {e}")
                
    def ingest_text(self, text: str, chunk_by_headers: bool = True):
        """
        Ingest text content into the knowledge base.
        """
        if not self.is_ready:
            print("KnowledgeBase not ready (no API key or lib)")
            return
            
        chunks = self._chunk_text(text) if chunk_by_headers else [text]
        
        print(f"Ingesting {len(chunks)} chunks...")
        for chunk in chunks:
            self._add_document(chunk)
            
    def _chunk_text(self, text: str) -> List[str]:
        """Simple chunking by sections (markdown style ##)"""
        chunks = []
        current_chunk = []
        
        lines = text.split('\n')
        for line in lines:
            if line.strip().startswith('## '):
                if current_chunk:
                    chunks.append("\n".join(current_chunk))
                current_chunk = [line]
            else:
                current_chunk.append(line)
                
        if current_chunk:
            chunks.append("\n".join(current_chunk))
        return chunks

    def _add_document(self, text: str):
        """Add text, calculate embedding, store."""
        try:
            result = genai.embed_content(
                model=self.EMBEDDING_MODEL,
                content=text,
                task_type="retrieval_document"
            )
            embedding = result['embedding']
            self.documents.append(text)
            self.embeddings.append(embedding)
        except Exception as e:
            print(f"Failed to embed chunk: {e}")

    def search(self, query: str, top_k: int = 3, threshold: float = 0.35) -> List[Tuple[str, float]]:
        """
        Search for relevant documents.
        Returns list of (text, score).
        """
        if not self.is_ready or not self.embeddings:
            return []
            
        try:
            result = genai.embed_content(
                model=self.EMBEDDING_MODEL,
                content=query,
                task_type="retrieval_query"
            )
            query_embedding = result['embedding']
            
            scores = []
            
            if HAS_NUMPY:
                q_vec = np.array(query_embedding)
                q_norm = np.linalg.norm(q_vec)
                
                for doc_emb in self.embeddings:
                    d_vec = np.array(doc_emb)
                    # cosine similarity
                    denom = (q_norm * np.linalg.norm(d_vec))
                    similarity = np.dot(q_vec, d_vec) / denom if denom > 0 else 0
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
            
            # Get top K
            indexed_scores = list(enumerate(scores))
            indexed_scores.sort(key=lambda x: x[1], reverse=True)
            
            results = []
            for idx, score in indexed_scores[:top_k]:
                if score > threshold:
                    results.append((self.documents[idx], score))
            
            return results
            
        except Exception as e:
            print(f"Search failed: {e}")
            return []
            
    def clear(self):
        """Clear knowledge base"""
        self.documents = []
        self.embeddings = []
